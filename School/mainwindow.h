#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "studentsignup.h"
#include "teachersignup.h"
#include <QMainWindow>
#include <QStringListModel>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_manageStudents_clicked();

    void on_manageTeachers_clicked();

    void on_manageSchoolDay_clicked();

    void returnToHomePage();

    void on_addStudent_clicked();

    void on_studentInfo_clicked();

    void on_expellStudent_clicked();

    void on_hireTeacher_clicked();

    void on_teacherInfo_clicked();

    void on_fireTeacher_clicked();

    void on_startExam_clicked();

    void on_breaktime_clicked();

    void on_lunchtime_clicked();

    void on_classTrip_clicked();

private:
    Ui::MainWindow *ui;

    StudentSignUp *studentSignUp;
    TeacherSignUp *teacherSignUp;
    QStringListModel *studentListModel;
    QStringListModel *teacherListModel;

    void setUpStudents();

    void setUpTeachers();

};
#endif // MAINWINDOW_H
