#include "teachersignup.h"
#include "ui_teachersignup.h"

#include "database.h"

TeacherSignUp::TeacherSignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherSignUp)
{
    ui->setupUi(this);

    ui->subject->setModel(&Database::subjects);
}

TeacherSignUp::~TeacherSignUp()
{
    delete ui;
}

void TeacherSignUp::closeEvent(QCloseEvent *event)
{
    ui->name->clear();
    ui->subject->setCurrentIndex(0);
}

void TeacherSignUp::on_hireTeacher_clicked()
{
    QString name = ui->name->text();
    QString subject = ui->subject->currentText();
    if(name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please provide a name");
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't connect to database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("INSERT INTO teacher(teacher_name, subject) VALUES('"+name+"', '"+subject+"');")) {
        QMessageBox::warning(this, "Error", "Couldn't hire teacher: \n" + qry.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Hired teacher");
    Database::db.close();
}

