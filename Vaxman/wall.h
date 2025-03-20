#ifndef WALL_H
#define WALL_H

/*
 * Description: A black square that neither the player nor ghosts can cross
*/

#include "vector.h"

#include <QGraphicsItem>

#include <QRectF>
#include <QBrush>
#include <QPainter>

class Wall : public QGraphicsItem
{
    int width;
    int height;

public:

    Vector position;


    Wall(int width, int hheight, Vector position);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int step);

};

#endif // WALL_H
