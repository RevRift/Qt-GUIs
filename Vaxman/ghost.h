#ifndef GHOST_H
#define GHOST_H

/*
 * Description: Represents ghost that the user will vaccinate
*/

#include "vector.h"

#include <QGraphicsEllipseItem>
#include <QRectF>
#include <QBrush>
#include <QPainter>

class Ghost : public QGraphicsEllipseItem
{
    int width;
    int height;

public:

    Vector position;
    Vector direction;
    Vector nextDirection;
    int speed;

    Ghost(int width, int height, Vector position, Vector direction, int speed);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int step);
};

#endif // GHOST_H
