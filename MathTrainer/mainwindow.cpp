#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->MathTrainer);
    ui->MathTrainer->setCurrentWidget(ui->homePage);

    timer.setSingleShot(false);
    timer.setInterval(1000);
    remainingTime = 60;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateRemainingTime()));
    ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime));

    QFile readHighscore(":/data/MathTrainerHighscore.txt");
    if(readHighscore.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&readHighscore);
        highscore = in.readLine().toInt();
        ui->highscoreLabel->setText("Highscore: " + QString::number(highscore));
        readHighscore.close();
    } else {
        highscore = -1;
        ui->highscoreLabel->setText("Highscore: N/A");
        QMessageBox::warning(this, "WARNING", "Couldn't read 'MathTrainerHighscore.txt'");
    }

    sessionBest = -1;
    sessionRounds = 0;
    sessionPoints = 0;
    points = 0;
    addedPoints = 10;
    ui->pointsLabel->setText("Points: " + QString::number(points));
    pointTimer.setSingleShot(false);
    pointTimer.setInterval(500);
    connect(&pointTimer, SIGNAL(timeout()), this, SLOT(decrementAddedPoints()));

    connect(ui->option1, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(ui->option2, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    connect(ui->option3, SIGNAL(clicked()), this, SLOT(checkAnswer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_train_released()
{
    ui->MathTrainer->setCurrentWidget(ui->trainPage);
    generateQuestion();
    timer.start();
}

void MainWindow::updateRemainingTime()
{
    remainingTime--;
    ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime));

    if(remainingTime == 0) {
        timer.stop();

        // process points
        sessionRounds++;
        sessionPoints += points;
        ui->sessionAverageLabel->setText("Session Average: " + QString::number(sessionPoints/sessionRounds));
        if(points > sessionBest) {
            sessionBest = points;
            ui->sessionBestLabel->setText("Session Best: " + QString::number(sessionBest));
            if(highscore != -1 && points > highscore) {
                QFile writeHighscore("C:/Users/Oksta/OneDrive/Desktop/Programming/C++/Qt_GUIs/MathTrainer/MathTrainerHighscore.txt");
                if(writeHighscore.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    highscore = points;
                    ui->highscoreLabel->setText("Highscore: " + QString::number(highscore));
                    QTextStream out(&writeHighscore);
                    out << highscore;
                    writeHighscore.flush();
                    writeHighscore.close();
                } else {
                    QMessageBox::information(this, "WARNING", "Couldn't save highscore");
                }
            }
        }

        // reset
        points = 0;
        ui->pointsLabel->setText("Points: " + QString::number(points));
        remainingTime = 60;
        ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime));
        ui->MathTrainer->setCurrentWidget(ui->homePage);
    }
}


void MainWindow::on_back_released()
{
    timer.stop();

    // reset scoring and timer
    remainingTime = 60;
    ui->remainingTimeLabel->setText("Remaining Time: " + QString::number(remainingTime));
    points = 0;
    ui->pointsLabel->setText("Points: " + QString::number(points));

    ui->MathTrainer->setCurrentWidget(ui->homePage);
}

void MainWindow::checkAnswer()
{
    if(pointTimer.isActive())
        pointTimer.stop();
    QPushButton *option = static_cast<QPushButton *>(sender());
    if(option->text().toInt() == answer) {
        points += addedPoints;
    } else {
        points = (points-5 <= 0) ? 0 : points-5;
    }
    ui->pointsLabel->setText("Points: " + QString::number(points));
    addedPoints = 10;
    generateQuestion();
}

void MainWindow::decrementAddedPoints()
{
    if(addedPoints > 1) {
        addedPoints--;
    } else {
        pointTimer.stop();
    }
}

void MainWindow::generateQuestion()
{
    int num1 = rand() % 50 + 1;
    int num2 = rand() % 50 + 1;
    // operations = {'+', '-', '*', '/', '%'};
    int randOperation = rand() % 5;
    QList options = {0, 0, 0};
    switch(randOperation)
    {
        case 0: // add
        {
            answer = num1 + num2;
            ui->question->setText(QString::number(num1) + " + " +
                                  QString::number(num2));
            options[0] = (rand() % 2) ? answer-2 : answer+2;
            options[1] = answer;
            options[2] = (rand() % 2) ? answer+10 : answer-20;
        }   break;
        case 1: // substract
        {
            answer = num1 - num2;
            ui->question->setText(QString::number(num1) + " - " +
                                  QString::number(num2));
            options[0] = (rand() % 2) ? answer + 10 : -answer;
            options[1] = answer;
            options[2] = (answer < 0) ? answer-2 : answer+2;
        }   break;
        case 2: // multiply
        {
            num2 -= num2 % 10;
            answer = num1 * num2;
            ui->question->setText(QString::number(num1) + " x " +
                                  QString::number(num2));
            options[0] = (rand() % 2) ? answer-10 : answer+10;
            options[1] = answer;
            options[2] = (rand() % 2) ? answer-2 : answer+2;
        }   break;
        case 3: // divide
        {
            num2 = (rand() % 20) + 1;
            num1 = num2 * ((rand() % 20) + 1);
            answer = num1 / num2;
            ui->question->setText(QString::number(num1) + " / " +
                                  QString::number(num2));
            options[0] = answer-2;
            options[1] = answer;
            options[2] = answer+2;
        }   break;
        case 4: // mod
        {
            if(num1 < num2) std::swap(num1, num2);
            answer = num1 % num2;
            ui->question->setText(QString::number(num1) + " (mod " +
                                  QString::number(num2) + ")");
            options[0] = answer-2;
            options[1] = answer;
            options[2] = answer+2;
        }   break;
    }
    // set up correct answer option and two dummy options
    std::random_shuffle(options.begin(), options.end());
    ui->option1->setText(QString::number(options[0]));
    ui->option2->setText(QString::number(options[1]));
    ui->option3->setText(QString::number(options[2]));

    pointTimer.start();
}

