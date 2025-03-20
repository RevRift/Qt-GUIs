#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wall.h"
#include "player.h"
#include "ghost.h"
#include "dot.h"
#include "vector.h"

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static int WIDTH;
    static int HEIGHT;

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void advance();

    void duplicateGhosts();

    void endGame();

private:
    Ui::MainWindow *ui;

    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsTextItem *ghostCountText;
    QGraphicsTextItem *scoreText;
    QGraphicsTextItem *gameOverText;
    QTimer timer;
    QTimer duplicationTimer;
    QTimer endScreenTimer;

    QList<Wall *> walls;
    QList<Ghost *> ghosts;   
    QList<Dot *> dots;

    Player *player;
    int playerSpeed;
    int ghostSpeed;
    int dotCount;
    int ghostCount;
    int score;

    void movePlayer();

    void moveGhost(Ghost* ghost);

    bool willCollide(Vector position, Vector direction);

};
#endif // MAINWINDOW_H
