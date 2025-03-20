#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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
    void on_train_released();

    void updateRemainingTime();

    void on_back_released();

    void checkAnswer();

    void decrementAddedPoints();

private:
    Ui::MainWindow *ui;

    QTimer timer;
    QTimer pointTimer;
    int remainingTime;
    int highscore;
    int sessionBest;
    int sessionRounds;
    int sessionPoints;
    int points;   
    int addedPoints;
    int answer;

    void generateQuestion();
};
#endif // MAINWINDOW_H
