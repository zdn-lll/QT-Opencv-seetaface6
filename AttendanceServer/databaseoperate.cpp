#include "databaseoperate.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DataBaseOperate::DataBaseOperate()
{

}

QString DataBaseOperate::getColumnType(const QString &tableName, const QString &columnName, QSqlTableModel *model)
{
    QSqlDatabase db;
    if(model != nullptr)
        db = model->database();
    else
        db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "Database is not open!";
        return "";
    }
    QSqlQuery query(db);
        query.prepare("PRAGMA table_info(" + tableName + ");");

        if (!query.exec()) {
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return "";
        }

        while (query.next()) {
            QString name = query.value("name").toString();
            if (name == columnName) {
                QString type = query.value("type").toString();
                qDebug() << "Column name:" << columnName << ", Column type:" << type;
                return type;
            }
        }

        qDebug() << "Column" << columnName << "not found in table" << tableName;
        return "";
}

QString DataBaseOperate::getFilter(const QString &columnName, const QString &columnValue, QString &columnType)
{
    if(columnName.isEmpty() || columnValue.isEmpty() || columnType.isEmpty())
        return "";

    QString sqlFiter;
    if(columnType == "INTEGER" || columnName == "REAL")
    {
        sqlFiter = columnName + "=" + columnValue;
    }
    else
    {
        sqlFiter = columnName + "=\"" + columnValue + "\"";
    }

    return sqlFiter;
}

bool DataBaseOperate::startTransaction(QSqlTableModel *model)
{
    QSqlDatabase db;
    if(model != nullptr)
        db = model->database();
    else
        db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "Database is not open!";
        return false;
    }
    if(!db.transaction())
    {
        qDebug() << "Error: unable to start transaction" << db.lastError();
        return false;
    }
    return true;
}

bool DataBaseOperate::startCommit(QSqlTableModel *model)
{
    QSqlDatabase db;
    if(model != nullptr)
        db = model->database();
    else
        db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "Database is not open!";
        return false;
    }
    if(!db.commit())
    {
         qDebug() << "Error: commit failed" << db.lastError();
         return false;
    }
    else
    {
        qDebug() << "Transaction committed successfully";
        model->submitAll();
        return true;
    }
}

bool DataBaseOperate::startRollback(QSqlTableModel *model)
{
    QSqlDatabase db;
        if(model != nullptr)
            db = model->database();
        else
            db = QSqlDatabase::database();
        if (!db.isOpen())
        {
            qDebug() << "Database is not open!";
            return false;
        }
        if(!db.rollback())
        {
             qDebug() << "Error: rollback failed" << db.lastError();
             return false;
        }
        else
        {
            qDebug() << "Transaction rolled back successfully";
            model->select(); // Refresh the model
            return true;
        }

}

void DataBaseOperate::deleteSelectedRows(QSqlTableModel *model, QTableView *view)
{
    QItemSelectionModel* selectionModel = view->selectionModel();
        QModelIndexList selectedRows = selectionModel->selectedRows();

        if (selectedRows.isEmpty()) {
            qDebug() << "No rows selected";
            return;
        }

        // Sort rows in descending order to avoid index shifting issues
        std::sort(selectedRows.begin(), selectedRows.end(), [](const QModelIndex &a, const QModelIndex &b) {
            return a.row() > b.row();
        });

        for (const QModelIndex &index : selectedRows) {
            model->removeRow(index.row());
        }

        model->select(); // Refresh the model
}


