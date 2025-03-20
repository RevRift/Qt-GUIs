#include "studentsignup.h"
#include "ui_studentsignup.h"

#include "database.h"

StudentSignUp::StudentSignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentSignUp)
{
    ui->setupUi(this);

    ui->subject1->setModel(&Database::subjects);
    ui->subject2->setModel(&Database::subjects);
    ui->subject3->setModel(&Database::subjects);
}

StudentSignUp::~StudentSignUp()
{
    delete ui;
}

void StudentSignUp::closeEvent(QCloseEvent *event)
{
    event->accept();
    ui->name->clear();
    ui->subject1->setCurrentIndex(0);
    ui->subject2->setCurrentIndex(0);
    ui->subject3->setCurrentIndex(0);
}

void StudentSignUp::on_addStudent_clicked()
{
    QString name = ui->name->text();
    QString subject1 = ui->subject1->currentText();
    QString subject2 = ui->subject2->currentText();
    QString subject3 = ui->subject3->currentText();
    if(name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please provide a name");
        return;
    } else if(subject1 == subject2 || subject2 == subject3 || subject1 == subject3) {
        QMessageBox::warning(this, "Error", "Duplicate Subjects");
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't connect to database: \n" + Database::db.lastError().text());
        return;
    }

    QSqlQuery qry;
    if(!qry.exec("INSERT INTO student(student_name, subjects) VALUES('"+name+"', '"+subject1+"  "+subject2+"  "+subject3+"');")) {
        QMessageBox::warning(this, "Error", "Couldn't add student: \n" + qry.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Added student");
    Database::db.close();
}

