#include "dot.h"

Dot::Dot(int width, int height, Vector position) :
    width(width), height(height), position(position)
{}

QRectF Dot::boundingRect() const
{
    return QRectF(2, 2, width-4, height-4);;
}

void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::yellow));

    painter->drawEllipse(QPointF(width/2, height/2), 5, 5);
}

void Dot::advance(int step)
{
    if(!step) return;

    setPos(x(), y());
}
