#include "player.h"

Player::Player(int width, int height, Vector position, Vector direction, int speed) :
    width(width), height(height), position(position), direction(direction), speed(speed)
{
    nextDirection = direction;
}

QRectF Player::boundingRect() const
{
    return QRectF(2, 2, width-4, height-4);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(Qt::yellow));

    painter->drawEllipse(QPointF(width/2, height/2), width/2-2, height/2-2);
}

void Player::advance(int step)
{
    if(!step) return;

    // if vaxman is going through wall, it teleports to the opposite side
    if(x() < 0 && direction == Vector(-1, 0)) {
        setPos(x() + (15*width), y());
        position.x = 14;
        return;
    } else if(x() > (14*width) && direction == Vector(1, 0)) {
        setPos(x() - (15*width), y());
        position.x = 0;
        return;
    } else if(y() < 0 && direction == Vector(0, -1)) {
        setPos(x(), y() + (15*height));
        position.y= 14;
        return;
    } else if(y() > (14*height) && direction == Vector(0, 1)) {
        setPos(x(), y() - (15*height));
        position.y = 0;
        return;
    }

    // else move normally
    setPos(mapToParent(static_cast<int>(direction.x * speed), static_cast<int>(direction.y * speed)));
}
