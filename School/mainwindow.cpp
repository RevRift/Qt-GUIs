#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->schoolPages);
    ui->schoolPages->setCurrentWidget(ui->homePage);

    // set up buttons
    connect(ui->home1, SIGNAL(clicked()), this, SLOT(returnToHomePage()));
    connect(ui->home2, SIGNAL(clicked()), this, SLOT(returnToHomePage()));
    connect(ui->home3, SIGNAL(clicked()), this, SLOT(returnToHomePage()));

    ui->home1->raise();
    ui->home1->setGeometry(ui->studentImage->x(), ui->studentImage->y() + ui->studentImage->height() - ui->home1->height(),
                           ui->home1->width(), ui->home1->height());
    ui->home2->raise();
    ui->home2->setGeometry(ui->examImage->x(), ui->examImage->y() + ui->examImage->height() - ui->home2->height(),
                           ui->home2->width(), ui->home2->height());
    ui->startExam->raise();
    ui->startExam->setGeometry(ui->examImage->x() + ui->examImage->width() - ui->startExam->width(), ui->examImage->y(),
                           ui->startExam->width(), ui->startExam->height());
    ui->home3->raise();
    ui->home3->setGeometry(ui->classTripImage->x(), ui->classTripImage->y() + ui->classTripImage->height() - ui->home3->height(),
                           ui->home3->width(), ui->home3->height());

    //images
    QImage image;
    if(!image.load(":/images/school.png")) {
        QMessageBox::information(this, "Error", "Couldn't load 'school' image");
    } else {
        image = image.scaledToHeight(ui->schoolImage->height());
        image = image.scaledToWidth(ui->schoolImage->width());
        ui->schoolImage->setPixmap(QPixmap::fromImage(image));
    }
    if(!image.load(":/images/student.png")) {
        QMessageBox::information(this, "Error", "Couldn't load 'student' image");
    } else {
        image = image.scaledToHeight(ui->studentImage->height());
        image = image.scaledToWidth(ui->studentImage->width());
        ui->studentImage->setPixmap(QPixmap::fromImage(image));
    }
    if(!image.load(":/images/exam.png")) {
        QMessageBox::information(this, "Error", "Couldn't load 'exam' image");
    } else {
        image = image.scaledToHeight(ui->examImage->height());
        image = image.scaledToWidth(ui->examImage->width());
        ui->examImage->setPixmap(QPixmap::fromImage(image));
    }
    if(!image.load(":/images/classTrip.png")) {
        QMessageBox::information(this, "Error", "Couldn't load 'class trip' image");
    } else {
        image = image.scaledToHeight(ui->classTripImage->height());
        image = image.scaledToWidth(ui->classTripImage->width());
        ui->classTripImage->setPixmap(QPixmap::fromImage(image));
    }

    // database storing students, teachers and subjects at school
    Database::setUpDatabase();

    studentSignUp = new StudentSignUp(this);
    // style sheet here
    studentSignUp->setModal(true);
    studentListModel = new QStringListModel(this);
    setUpStudents();

    teacherSignUp = new TeacherSignUp(this);
    // style sheet here
    teacherSignUp->setModal(true);
    teacherListModel = new QStringListModel(this);
    setUpTeachers();





}

MainWindow::~MainWindow()
{
    delete ui;
}

/************************************ Navigate pages *****************************************/

void MainWindow::on_manageStudents_clicked()
{ ui->schoolPages->setCurrentWidget(ui->studentsPage); }

void MainWindow::on_manageTeachers_clicked()
{ ui->schoolPages->setCurrentWidget(ui->teachersPage); }

void MainWindow::on_manageSchoolDay_clicked()
{ ui->schoolPages->setCurrentWidget(ui->schoolDayPage); }

void MainWindow::returnToHomePage()
{ ui->schoolPages->setCurrentWidget(ui->homePage); }

/************************************ Set up students and teachers *****************************************/

void MainWindow::setUpStudents()
{
    QStringList studentNames;
    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database:\n" + Database::db.lastError().text());
        return;
    }

    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM student")) {
        QMessageBox::warning(this, "Error", "Couldn't find students:\n" + qry.lastError().text());
    } else {
        while(qry.next()) {
            studentNames.emplace_back(qry.value(1).toString());
        }
        studentListModel->setStringList(studentNames);
        ui->studentsComboBox->setModel(studentListModel);
    }

    Database::db.close();
}

void MainWindow::setUpTeachers()
{
    QStringList teacherNames;
    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database:\n" + Database::db.lastError().text());
        return;
    }

    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM teacher")) {
        QMessageBox::warning(this, "Error", "Couldn't find teachers:\n" + qry.lastError().text());
    } else {
        while(qry.next())
            teacherNames.emplace_back(qry.value(1).toString());
        teacherListModel->setStringList(teacherNames);
        ui->teachersComboBox->setModel(teacherListModel);
    }

    Database::db.close();
}

/************************************ Manage students *****************************************/

void MainWindow::on_addStudent_clicked()
{
    studentSignUp->exec();
    setUpStudents(); // update
}

void MainWindow::on_studentInfo_clicked()
{
    if(ui->studentsComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no students" + Database::db.lastError().text());
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM student WHERE student_name = '" + ui->studentsComboBox->currentText() + "';")) {
        QMessageBox::warning(this, "Error", "Couldn't find student: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    qry.next();

    QString aboutText;
    aboutText += "\nName: " + qry.value(1).toString();
    aboutText += "\nSubjects: " + qry.value(2).toString();
    QString performance = qry.value(3).toString();
    if(performance.isEmpty()) performance = "N/A";
    aboutText += "\nPerformance: " + performance;
    QMessageBox::about(this, "About student", aboutText);

    Database::db.close();
}

void MainWindow::on_expellStudent_clicked()
{
    if(ui->studentsComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no students" + Database::db.lastError().text());
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("DELETE FROM student WHERE student_name = '" + ui->studentsComboBox->currentText() + "';")) {
        QMessageBox::warning(this, "Error", "Couldn't find student: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    setUpStudents(); // maybe i don't have to set everything up again but idc
    Database::db.close();
    QMessageBox::information(this, "Success", "Student expelled");
}

/************************************** Manage teachers *****************************************/

void MainWindow::on_hireTeacher_clicked()
{
    teacherSignUp->exec();
    setUpTeachers(); // update
}

void MainWindow::on_teacherInfo_clicked()
{
    if(ui->teachersComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no teachers" + Database::db.lastError().text());
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM teacher WHERE teacher_name = '" + ui->teachersComboBox->currentText() + "';")) {
        QMessageBox::warning(this, "Error", "Couldn't find teacher: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    qry.next();

    QString aboutText;
    aboutText += "\nName: " + qry.value(1).toString();
    aboutText += "\nSubject: " + qry.value(2).toString();
    QString performance = qry.value(3).toString();
    if(performance.isEmpty()) performance = "N/A";
    aboutText += "\nPerformance: " + performance;
    QMessageBox::about(this, "About teacher", aboutText);

    Database::db.close();
}

void MainWindow::on_fireTeacher_clicked()
{
    if(ui->teachersComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no teachers" + Database::db.lastError().text());
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("DELETE FROM teacher WHERE teacher_name = '" + ui->teachersComboBox->currentText() + "';")) {
        QMessageBox::warning(this, "Error", "Couldn't find teacher: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    setUpTeachers();
    Database::db.close();
    QMessageBox::information(this, "Success", "Teacher fired");
}

void MainWindow::on_startExam_clicked()
{
    if(ui->teachersComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no teachers");
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }

    QString examiner = ui->teachersComboBox->currentText(); // teacher
    QSqlQuery qry;
    if(!qry.exec("SELECT teacher.subject FROM teacher WHERE teacher_name = '" + examiner + "';")) {
        QMessageBox::warning(this, "Error", "Couldn't find teacher: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    qry.next();
    QString subject = qry.value(0).toString();
    if(!qry.exec("SELECT * FROM student WHERE student.subjects LIKE '%"+subject+"%'")) {
        QMessageBox::warning(this, "Error", "Couldn't find students who took "+subject+": \n" + qry.lastError().text());
        Database::db.close();
        return;
    }

    std::vector<std::pair<QString, int>> examinees;
    while(qry.next()) {
        QSqlQuery update;
        QString examinee = qry.value(1).toString();        
        int newPerformance = rand() % 100 + 1;
        int lastPerformance = (qry.value(3).toString().isEmpty()) ? newPerformance : qry.value(3).toInt();
        if(!update.exec("UPDATE student SET performance = "+
                        QString::number((lastPerformance+newPerformance)/2)+
                        " WHERE student_id = "+
                        QString::number(qry.value(0).toInt())+";")) {
            QMessageBox::warning(this, "Error", "Couldn't make students do test:\n" + update.lastError().text());
            Database::db.close();
            break;
        }
        examinees.push_back({examinee, newPerformance});
    }
    if(examinees.empty()) {
        QMessageBox::information(this, "No students", "No students took "+subject);
        Database::db.close();
        return;
    }

    QString aboutText;
    aboutText += "\n"+examiner+" started a "+subject+" test\n";
    for(std::pair<QString, int> &examinee : examinees)
        aboutText += "\n"+examinee.first+" scored "+QString::number(examinee.second);
    QMessageBox::about(this, subject+" test", aboutText);

    Database::db.close();
}

/************************************** Manage school day *****************************************/

void MainWindow::on_breaktime_clicked()
{
    if(ui->teachersComboBox->count() == 0 && ui->studentsComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no students or teachers");
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM teacher;")) {
        QMessageBox::warning(this, "Error", "Couldn't find teachers: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    QString aboutText;
    while(qry.next()) {
        if(rand() % 2)
            aboutText += qry.value(1).toString()+" is on duty\n";
        else
            aboutText += qry.value(1).toString()+" is reading a "+qry.value(2).toString()+" book\n";
    }
    if(!qry.exec("SELECT student_name FROM student;")) {
        QMessageBox::warning(this, "Error", "Couldn't find students: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    QString studentActivities[6] = {"is playing", "is dancing", "is eating", "is crying", "is bored", "is hiding"};
    while(qry.next()) {
        aboutText += "\n"+qry.value(0).toString()+" "+studentActivities[rand()%6]+" in the playground";
    }
    QMessageBox::about(this, "Breaktime", aboutText);

    Database::db.close();
}

void MainWindow::on_lunchtime_clicked()
{
    if(ui->teachersComboBox->count() == 0 && ui->studentsComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no students or teachers");
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }
    QSqlQuery qry;
    if(!qry.exec("SELECT teacher_name FROM teacher;")) {
        QMessageBox::warning(this, "Error", "Couldn't find teachers: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    QString aboutText;
    while(qry.next()) {
        aboutText += qry.value(0).toString()+" is eating a healthy meal\n";
    }

    if(!qry.exec("SELECT student_name FROM student;")) {
        QMessageBox::warning(this, "Error", "Couldn't find students: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    QString activities[4] = {"is eating pizza", "is eating rice", "is eating the school meal", "is looking for food"};
    while(qry.next()) {
        aboutText += "\n"+qry.value(0).toString()+" "+activities[rand()%4]+" in the playground";
    }
    QMessageBox::about(this, "Lunchtime", aboutText);

    Database::db.close();
}

void MainWindow::on_classTrip_clicked()
{
    if(ui->teachersComboBox->count() == 0) {
        QMessageBox::warning(this, "Error", "There are no teachers to supervise the trip");
        return;
    }

    if(!Database::db.open()) {
        QMessageBox::warning(this, "Error", "Couldn't open database: \n" + Database::db.lastError().text());
        return;
    }

    QSqlQuery qry;
    if(!qry.exec("SELECT * FROM teacher ORDER BY RANDOM() LIMIT 1;")) {
        QMessageBox::warning(this, "Error", "Couldn't find teacher: \n" + qry.lastError().text());
        Database::db.close();
        return;
    }
    qry.next();
    QString supervisor = qry.value(1).toString();
    QString subject = qry.value(2).toString();

    if(supervisor.isEmpty()) {
        QMessageBox::warning(this, "Error", "There are no teachers to supervise the trip");
        Database::db.close();
        return;
    }

    if(!qry.exec("SELECT * FROM student WHERE student.subjects LIKE '%"+subject+"%'")) {
        QMessageBox::warning(this, "Error", "Couldn't find students who took "+subject+": \n" + qry.lastError().text());
        Database::db.close();
        return;
    }

    QStringList students;
    while(qry.next()) {
        students.emplace_back(qry.value(1).toString());
    }
    if(students.empty()) {
        QString aboutText;
        aboutText += "\n"+supervisor+" went to the museum alone because no students took "+subject;
        QMessageBox::about(this, "Lonely trip to museum", aboutText);
        Database::db.close();
        return;
    }

    QString aboutText;
    aboutText += "\n"+supervisor+" took "+QString::number(students.size())+" students on a trip to the "+subject+" section of the museum\n";
    for(QString &student : students)
        aboutText += "\n"+student+" went along";
    QMessageBox::about(this, "Trip to museum", aboutText);

    Database::db.close();
}

