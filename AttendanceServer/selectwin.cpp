#include "selectwin.h"
#include "ui_selectwin.h"
#include <QFileDialog>
#include <QDebug>

#include "databaseoperate.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QMessageBox>
#include <QRadioButton>

SelectWin::SelectWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectWin)
{
    ui->setupUi(this);
    model = new QSqlTableModel();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    dbOperator = new DataBaseOperate;
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

SelectWin::~SelectWin()
{
    delete ui;
    delete  model;
    delete  dbOperator;
}

bool SelectWin::exportData2XLSX(QString fileName, QString tableName)
{
    QXlsx::Document xlsx;
        QXlsx::Format format1;/*设置标题单元的样式*/
        format1.setFontSize(12);/*设置字体大小*/
        format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
        //format1.setBorderStyle(QXlsx::Format::BorderThin);/*边框样式*/
        //format1.setFontBold(true);/*设置加粗*/

        if(!xlsx.selectSheet("表格数据")){/*在当前打开的xlsx文件中，找一个名字为ziv的sheet*/
            xlsx.addSheet("表格数据");//找不到的话就添加一个名为ziv的sheet
        }

//        QSqlDatabase db = QSqlDatabase::database();
        QSqlDatabase db = model->database();
        QString sqlFiter = model->filter();
        if(!sqlFiter.isEmpty())
            sqlFiter = " WHERE " + sqlFiter;
//        qDebug() << sqlFiter;
        QString tmpSql = QString("SELECT * FROM %1" + sqlFiter).arg(tableName);
        QSqlQuery query(db);
        if(query.exec(tmpSql)){
            //表头列
            QSqlRecord queryRecord(query.record());
            qDebug()<<"queryRecord.count():"<<queryRecord.count();
            for(int colNum = 0; colNum < queryRecord.count(); colNum++){
                //qDebug() <<  queryRecord.fieldName(colNum);
                xlsx.write(1, colNum+1,  queryRecord.fieldName(colNum),format1);
            }

            //表格数据
            int rowNum = 2;
            while(query.next()){
                for(int colNum = 0; colNum < queryRecord.count(); colNum++){
                    xlsx.write(rowNum, colNum + 1, query.value(colNum),format1);
                }
                rowNum++;
            }
        }else{
            qDebug() << "sql语句执行失败";
            return false;
        }

        if(fileName.isEmpty())
        {
            qDebug() << "文件为空";
            return false;
        }

        xlsx.saveAs(fileName);//保存文件

        return true;
}

void SelectWin::setFilterBoxOptioins(QSqlTableModel *model)
{
    QStringList columnNames;
    int columnCount = model->columnCount();

    for (int i = 0; i < columnCount; ++i)
    {
        QString  columnName = model->headerData(i, Qt::Horizontal).toString();
        columnNames << columnName;
    }

    ui->filterBox->addItems(columnNames);
}

void SelectWin::reSetFilterBoxOptioins(QString defaultOption)
{
    ui->filterBox->clear();
    ui->filterBox->addItem(defaultOption);
}

void SelectWin::on_selectBt_clicked()
{
    model->select();
    QString sqlFiter;
    if(ui->filterBox->currentText() != "default")
    {
        if(!ui->filterEdit->text().isEmpty())
        {
            QString type = dbOperator->getColumnType(model->tableName(), ui->filterBox->currentText(), model);
            sqlFiter = dbOperator->getFilter(ui->filterBox->currentText(), ui->filterEdit->text(), type);
            model->setFilter(sqlFiter);
        }
        else
        {
            sqlFiter.clear();
            model->setFilter(sqlFiter);
        }
    }
    else
    {
        sqlFiter.clear();
        model->setFilter(sqlFiter);
    }
    qDebug() << model->filter();

    ui->tableView->setModel(model);
    /***********测试************/
    QObject::connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
            QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
            if (!selectedIndexes.isEmpty()) {
                for (const QModelIndex &index : selectedIndexes) {
                    QString columnName = model->headerData(index.column(), Qt::Horizontal).toString();
                    QString rowName = model->headerData(index.row(), Qt::Vertical).toString();
                    qDebug() << "Selected cell at row:" << index.row() << "column:" << index.column();
                    qDebug() << "Selected cell at row:" << rowName << "column:" << columnName;
                    qDebug() << index.data().toString();
                }
            }
        });
    /***********测试************/
}

void SelectWin::on_exportBt_clicked()
{
    QString exportPath = QFileDialog::getExistingDirectory(this);
    ui->excelPathEdit->setText(exportPath);
}

void SelectWin::on_startExportBt_clicked()
{
    QString tableName;
    QString fileName;
    QString filePath = ui->excelPathEdit->text();
    if(filePath.isEmpty())
    {
        QMessageBox::information(this, "导出提示", "请选择导出路径");
        return;
    }
    if(ui->empRb->isChecked())
    {
        tableName = "employee";
        fileName = filePath + "/employee.xlsx";
    }
    if(ui->attRb->isChecked())
    {
        tableName = "attendance";
        fileName = filePath + "/attendance.xlsx";
    }
    if(tableName.isEmpty() || fileName.isEmpty())
    {
        QMessageBox::information(this, "导出提示", "请选择需要导出的表格");
        return;
    }
    if(exportData2XLSX(fileName, tableName))
    {
        qDebug() << "导出成功";
    }
    else {
        qDebug() << "导出失败";
    }
}

void SelectWin::on_empRb_clicked()
{
    reSetFilterBoxOptioins();
    if(ui->empRb->isChecked())
    {
        model->setTable("employee");
    }
    setFilterBoxOptioins(model);
}

void SelectWin::on_attRb_clicked()
{
    reSetFilterBoxOptioins();
    if(ui->attRb->isChecked())
    {
        model->setTable("attendance");
    }
    setFilterBoxOptioins(model);
}

void SelectWin::on_transactionBt_clicked()
{
    if(ui->transactionBt->text() == "开始事务")
    {
        dbOperator->startTransaction(model);
        ui->transactionBt->setText("提交");
        ui->deletBt->setEnabled(true);
        ui->rollBackBt->setEnabled(true);
        ui->modifyBt->setEnabled(true);
        ui->startExportBt->setEnabled(false);
    }
    else
    {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "提交提示", "提交所有修改", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            dbOperator->startCommit(model);
            qDebug() << "Commit success";
            ui->transactionBt->setText("开始事务");
            ui->deletBt->setEnabled(false);
            ui->rollBackBt->setEnabled(false);
            ui->modifyBt->setEnabled(false);
            ui->startExportBt->setEnabled(true);
        }
        else
        {
            qDebug() << "Commit Cancal";
        }

    }
}

void SelectWin::on_rollBackBt_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "撤销提示", "撤销所有操作", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
    dbOperator->startRollback(model);
    dbOperator->startTransaction(model);
        qDebug() << "Roolback success";
    }
    else
    {
        qDebug() << "Roolback Cancal";
    }
}

void SelectWin::on_deletBt_clicked()
{
    dbOperator->deleteSelectedRows(model, ui->tableView);
}

void SelectWin::on_modifyBt_clicked()
{
    connect(model, &QAbstractItemModel::dataChanged, [](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
        qDebug() << "Data changed from" << topLeft << "to" << bottomRight;
    });
    if(ui->modifyBt->text() == "开启修改")
    {
        ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
        ui->transactionBt->setEnabled(false);
        ui->modifyBt->setText("关闭修改");
    }
    else
    {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->transactionBt->setEnabled(true);
        ui->modifyBt->setText("开启修改");
    }
}
