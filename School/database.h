#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QMessageBox>

class Database
{
public:
    Database();

    static QSqlDatabase db;
    static QStringListModel subjects;

    static void setUpDatabase();
};

#endif // DATABASE_H
