#ifndef TEACHERSIGNUP_H
#define TEACHERSIGNUP_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class TeacherSignUp;
}

class TeacherSignUp : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherSignUp(QWidget *parent = nullptr);
    ~TeacherSignUp();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_hireTeacher_clicked();

private:
    Ui::TeacherSignUp *ui;
};

#endif // TEACHERSIGNUP_H
