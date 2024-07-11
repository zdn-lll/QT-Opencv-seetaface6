#ifndef DATABASEOPERATE_H
#define DATABASEOPERATE_H

#include <QSqlTableModel>
#include <QTableView>


class DataBaseOperate
{
public:
    DataBaseOperate();
    QString getColumnType(const QString &tableName, const QString &columnName, QSqlTableModel *model = nullptr);
    QString getFilter(const QString &columnName, const QString &columnValue, QString &columnType);
    bool startTransaction(QSqlTableModel *model = nullptr);
    bool startCommit(QSqlTableModel *model = nullptr);
    bool startRollback(QSqlTableModel *model = nullptr);
    void deleteSelectedRows(QSqlTableModel* model, QTableView* view);
};

#endif // DATABASEOPERATE_H
