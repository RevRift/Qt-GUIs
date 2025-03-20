#ifndef PLAYER_H
#define PLAYER_H

/*
 * Description: Represents Vax-man that the user will control
*/

#include "vector.h"

#include <QGraphicsEllipseItem>
#include <QRectF>
#include <QBrush>
#include <QPainter>

class Player : public QGraphicsEllipseItem
{
    int width;
    int height;

public:

    Vector position;
    Vector direction;
    Vector nextDirection;
    int speed;

    Player(int width, int height, Vector position, Vector direction, int speed);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int step);
};

#endif // PLAYER_H
