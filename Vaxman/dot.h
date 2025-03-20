#ifndef DOT_H
#define DOT_H

/*
 * A small yellow circle to user can claim (delete)
*/

#include "vector.h"

#include <QGraphicsEllipseItem>
#include <QRectF>
#include <QBrush>
#include <QPainter>

class Dot : public QGraphicsEllipseItem
{
    int width;
    int height;

public:

    Vector position;

    Dot(int width, int height, Vector position);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void advance(int step);

};
#endif // DOT_H
