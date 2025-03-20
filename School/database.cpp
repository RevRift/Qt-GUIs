#include "database.h"

Database::Database()
{}

void Database::setUpDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Oksta/OneDrive/Desktop/Programming/C++/Qt_GUIs/School/people.db");
    if(db.open()) {
        QSqlQuery qry;
        if(qry.exec("SELECT * FROM subject")) {
            QStringList subjectNames;
            while(qry.next()) {
                subjectNames.emplace_back(qry.value(1).toString());
            }
            subjects.setStringList(subjectNames);
        }
    }
}

QSqlDatabase Database::db;
QStringListModel Database::subjects;
