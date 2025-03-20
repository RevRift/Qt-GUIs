#include "wall.h"

Wall::Wall(int width, int height, Vector position) :
    width(width), height(height), position(position)
{}

QRectF Wall::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::green));

    painter->drawRect(boundingRect());
}

void Wall::advance(int step)
{
    if(!step) return;

    setPos(x(), y());
}
