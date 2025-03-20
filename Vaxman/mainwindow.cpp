#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // format page
    ui->menubar->hide();
    ui->statusbar->hide();
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("Vax-man");

    // set up graphics view
    view = new QGraphicsView(this);
    view->setSceneRect(0, 0, WIDTH, HEIGHT);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);

    view->show();
    view->setFocus();
    setCentralWidget(view);

    // set up graphics scene
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(Qt::black, Qt::BrushStyle::SolidPattern));
    view->setScene(scene);

    // set up walls
    walls = {
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 2)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 4)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 10)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 12)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(1, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(2, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(2, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(3, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(4, 0)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(4, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(4, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(4, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(4, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(4, 14)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(5, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(6, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(7, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(8, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(9, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(10, 0)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(10, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(10, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(10, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(10, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(10, 14)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 7)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(11, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(12, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(12, 13)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 1)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 2)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 3)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 4)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 5)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 6)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 8)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 9)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 10)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 11)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 12)),
        new Wall(WIDTH/15, HEIGHT/15, Vector(13, 13))
    };

    for(Wall *wall : walls)
    {
        wall->setPos(wall->position.x * WIDTH/15, wall->position.y * HEIGHT/15);
        scene->addItem(wall);
    }

    // set up dots
    dots = {
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 1)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 3)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 5)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 6)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 8)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 9)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 11)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 13)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(0, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(1, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(1, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(1, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 3)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 5)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 6)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 8)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 9)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 11)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(2, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 1)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 13)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(3, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 5)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 6)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 8)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 9)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(4, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 1)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 13)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(5, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(6, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(6, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(6, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(6, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(6, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(6, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 3)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 11)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(7, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(8, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(8, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(8, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(8, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(8, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(8, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 1)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 13)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(9, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 5)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 6)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 8)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 9)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(10, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 1)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 13)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(11, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 3)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 5)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 6)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 8)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 9)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 11)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(12, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(13, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(13, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(13, 14)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 0)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 1)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 2)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 3)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 4)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 5)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 6)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 7)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 8)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 9)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 10)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 11)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 12)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 13)),
        new Dot(WIDTH/15, HEIGHT/15, Vector(14, 14)),
    }; // lol

    for(Dot *dot : dots)
    {
        dot->setPos(dot->position.x * WIDTH/15, dot->position.y * HEIGHT/15);
        scene->addItem(dot);
    }

    // set up ghosts
    ghostSpeed = 4; // must be a factor of player Speed
    ghosts = {
        new Ghost(WIDTH/15, HEIGHT/15, Vector(11, 0), Vector(0, 1), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(7, 2), Vector(1, 0), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(7, 12), Vector(-1, 0), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(12, 12), Vector(-1, 0), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(2, 12), Vector(0, -1), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(2, 2), Vector(0, 1), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(7, 4), Vector(-1, 0), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(7, 10), Vector(1, 0), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(9, 14), Vector(-1, 0), ghostSpeed),
        new Ghost(WIDTH/15, HEIGHT/15, Vector(0, 13), Vector(0, 1), ghostSpeed),
    };

    ghostCount = static_cast<int>(ghosts.size());

    for(Ghost *ghost : ghosts)
    {
        ghost->setPos(ghost->position.x * WIDTH/15, ghost->position.y * HEIGHT/15);
        scene->addItem(ghost);
    }

    // set up text
    ghostCountText = new QGraphicsTextItem();
    ghostCountText->setFont(QFont("Times", 10, QFont::Bold));
    ghostCountText->setHtml("Ghost count: " + QString::number(ghostCount));
    ghostCountText->setPos(9 * WIDTH/15 - 50, 5 * HEIGHT/15);
    scene->addItem(ghostCountText);

    score = 0;
    scoreText = new QGraphicsTextItem();
    scoreText->setFont(QFont("Times", 10, QFont::Bold));
    scoreText->setHtml("Score: " + QString::number(score));
    scoreText->setPos(9 * WIDTH/15 - 30, 9 * HEIGHT/15 + 10);
    scene->addItem(scoreText);

    gameOverText = new QGraphicsTextItem();
    gameOverText->setFont(QFont("Times?", 30, QFont::Bold));
    gameOverText->setPos(WIDTH/2 - 85, HEIGHT/2 - 30);

    // set up player;
    playerSpeed = 8; // must be a factor of 40
    player = new Player(WIDTH/15, HEIGHT/15, Vector(0, 0), Vector(0, 0), playerSpeed);
    player->setPos(player->position.x * WIDTH/15, player->position.y * HEIGHT/15);
    scene->addItem(player);

    // set up timers to update game state
    connect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
    connect(&duplicationTimer, SIGNAL(timeout()), this, SLOT(duplicateGhosts()));
    connect(&endScreenTimer, SIGNAL(timeout()), this, SLOT(endGame()));
    timer.setInterval(40);
    timer.start();
    duplicationTimer.setInterval(10000); // 10s
    duplicationTimer.start();
    endScreenTimer.setInterval(3000); // 3s
}

int MainWindow::WIDTH;
int MainWindow::HEIGHT;

MainWindow::~MainWindow()
{
    delete gameOverText;

    delete ghostCountText;

    delete scoreText;

    delete player;

    for(Ghost *ghost : ghosts)
    {
        delete ghost;
    }

    for (Dot *dot : dots)
    {
        delete dot;
    }

    for (Wall *wall : walls)
    {
        delete wall;
    }

    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    // only update direction if it won't result in the player getting stuck

        case Qt::Key_D:
        {
            if(!willCollide(player->position, Vector(1, 0)))
                player->nextDirection = Vector(1, 0);
        } break;

        case Qt::Key_A:
        {
            if(!willCollide(player->position, Vector(-1, 0)))
                player->nextDirection = Vector(-1, 0);
        } break;

        case Qt::Key_W:
        {
            if(!willCollide(player->position, Vector(0, -1)))
                player->nextDirection = Vector(0, -1);
        } break;

        case Qt::Key_S:
        {
            if(!willCollide(player->position, Vector(0, 1)))
                player->nextDirection = Vector(0, 1);
        } break;
    }
}



void MainWindow::advance()
{
    // if player is at dot, remove dot
    for(Dot *dot : dots)
    {
        if(dot->position == player->position)
        {
            score++;

            scene->removeItem(dot);
            delete dot;
            dots.removeOne(dot);
        }
    }

    // if ghost was vaccinated, remove it
    for(Ghost *ghost : ghosts)
    {
        if(ghost->position == player->position || ghost->position == player->position - player->direction)
        {
            score += 10;

            if(ghost->scene() == scene) // despite this check,
                scene->removeItem(ghost); // sometimes the program crashes when deleting a cluster of ghosts
            delete ghost;
            ghosts.removeOne(ghost);
            ghostCount--;
        }
    }

    // update text;
    ghostCountText->setHtml("Ghost count: " + QString::number(ghostCount));
    scoreText->setHtml("Score: " + QString::number(score));

    // move entities
    movePlayer();

    for(Ghost *ghost : ghosts)
    {
        moveGhost(ghost);
    }

    scene->advance();

    if(dots.empty())
    {
        // if there are not dots left, player wins
        gameOverText->setHtml("YOU WIN");
        scene->addItem(gameOverText);
        timer.stop();
        endScreenTimer.start();
    }

    if(ghostCount > 50)
    {
        // if ghost count exceeds 50, the player looses
        gameOverText->setHtml("YOU LOSE");
        scene->addItem(gameOverText);
        timer.stop();
        endScreenTimer.start();
    }
}

void MainWindow::movePlayer()
{
    // if player isn't on a new square, don't change direction
    if(static_cast<int>(player->x()) % 40 != 0 || static_cast<int>(player->y()) % 40 != 0)
        return;

    // update direction
    player->direction = player->nextDirection;

    // if player will hit a wall, stop the player and don't update position
    if(willCollide(player->position, player->direction)) {
        player->direction = Vector(0, 0);
        return;
    }

    // update position
    player->position = player->position + player->direction;
}

void MainWindow::moveGhost(Ghost* ghost)
{
    // if ghost isn't on a new square, don't change direction
    if(static_cast<int>(ghost->x()) % 40 != 0 || static_cast<int>(ghost->y()) % 40 != 0)
        return;

    QList<Vector> randDirections = {Vector(1, 0), Vector(-1, 0), Vector(0, 1), Vector(0, -1)};

    // if ghost will collide, change direction
    if(willCollide(ghost->position, ghost->direction))
    {
        ghost->direction = randDirections[rand() % 4];

        while(willCollide(ghost->position, ghost->direction))
            ghost->direction = randDirections[rand() % 4];
    }

    // else the ghost might (66% chance) turn at intersections
    else if(rand() % 3)
    {
        if(ghost->position == Vector(0, 0)) {
            ghost->direction = randDirections[rand() % 4];
        } else if(ghost->position == Vector(0, 7)) {
            ghost->direction = randDirections[rand() % 4];
        } else if(ghost->position == Vector(0, 14)) {
            ghost->direction = randDirections[rand() % 4];
        }
        else if(ghost->position == Vector(2, 4)) {
            randDirections.removeAt(1);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(2, 7)) {
            randDirections.removeAt(0);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(2, 10)) {
            randDirections.removeAt(1);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(3, 2)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(3, 12)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(4, 4)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(4, 10)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(5, 0)) {
            randDirections.removeAt(1);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(5, 2)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(5, 12)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(5, 14)) {
            randDirections.removeAt(1);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(7, 2)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(7, 4)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(7, 10)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(7, 12)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(9, 0)) {
            randDirections.removeAt(0);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(9, 2)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(9, 12)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(9, 14)) {
            randDirections.removeAt(0);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(10, 4)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(10, 10)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(11, 2)) {
            randDirections.removeAt(2);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(11, 12)) {
            randDirections.removeAt(3);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(12, 4)) {
            randDirections.removeAt(0);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(12, 7)) {
            randDirections.removeAt(1);
            ghost->direction = randDirections[rand() % 3];
        } else if(ghost->position == Vector(12, 10)) {
            randDirections.removeAt(0);
            ghost->direction = randDirections[rand() % 3];
        }
        else if(ghost->position == Vector(14, 0)) {
            ghost->direction = randDirections[rand() % 4];
        } else if(ghost->position == Vector(14, 7)) {
            ghost->direction = randDirections[rand() % 4];
        } else if(ghost->position == Vector(14, 14)) {
            ghost->direction = randDirections[rand() % 4];
        }
    }

    // update position
    ghost->position = ghost->position + ghost->direction;
}

void MainWindow::duplicateGhosts()
{
    int size = ghosts.size();

    for(int i = 0; i < size; i++)
    {
        Ghost *newGhost = new Ghost(WIDTH/15, HEIGHT/15, ghosts[i]->position - ghosts[i]->direction, ghosts[i]->direction, ghostSpeed);
        newGhost->setPos(newGhost->position.x * WIDTH/15, newGhost->position.y * HEIGHT/15);
        ghosts.emplace_back(newGhost);
        scene->addItem(newGhost);
    }
    ghostCount *= 2;
}

bool MainWindow::willCollide(Vector position, Vector direction)
{
    // checks if entity will hit a wall on the next move

    Vector nextPosition = position + direction;

    for(Wall *wall : walls)
    {
        if(wall->position == nextPosition)
            return true;
    }
    return false;
}
// (the above function fails when the direction teleports the entity to the opposite side,
//  but due to the layout of this map, this won't cause any problems)

void MainWindow::endGame()
{
    QApplication::quit();
}


