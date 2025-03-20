#ifndef STUDENTSIGNUP_H
#define STUDENTSIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class StudentSignUp;
}

class StudentSignUp : public QDialog
{
    Q_OBJECT

public:
    explicit StudentSignUp(QWidget *parent = nullptr);
    ~StudentSignUp();

protected:
    virtual void closeEvent(QCloseEvent* event);

private slots:
    void on_addStudent_clicked();

private:
    Ui::StudentSignUp *ui;
};

#endif // STUDENTSIGNUP_H
