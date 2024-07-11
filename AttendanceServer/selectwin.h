#ifndef SELECTWIN_H
#define SELECTWIN_H

#include "databaseoperate.h"

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>

namespace Ui {
class SelectWin;
}

class SelectWin : public QWidget
{
    Q_OBJECT

public:
    explicit SelectWin(QWidget *parent = nullptr);
    ~SelectWin();
    bool exportData2XLSX(QString fileName, QString tablename);
    void setFilterBoxOptioins(QSqlTableModel *model);
    void reSetFilterBoxOptioins(QString defaultOption = "default");

private slots:
    void on_selectBt_clicked();

    void on_exportBt_clicked();

    void on_startExportBt_clicked();

    void on_empRb_clicked();

    void on_attRb_clicked();

    void on_transactionBt_clicked();

    void on_rollBackBt_clicked();

    void on_deletBt_clicked();

    void on_modifyBt_clicked();

private:
    Ui::SelectWin *ui;
    QSqlTableModel *model;
    DataBaseOperate *dbOperator;
};

#endif // SELECTWIN_H
