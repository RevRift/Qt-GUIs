#include "vector.h"

Vector::Vector() :
    x(0), y(0)
{}

Vector::Vector(int x, int y) :
    x(x), y(y)
{}

Vector Vector::operator + (const Vector &other)
{
    Vector newVector = Vector(x + other.x, y + other.y);
    return newVector;
}

Vector Vector::operator - (const Vector &other)
{
    Vector newPosition = Vector(x - other.x, y - other.y);
    return newPosition;
}

Vector Vector::operator * (int multiplier)
{
    Vector newVector = Vector(x * multiplier, y * multiplier);
    return newVector;
}

bool Vector::operator == (const Vector &other)
{
    return (x == other.x && y == other.y);
}

bool Vector::operator !=(const Vector &other)
{
    return !(x == other.x && y == other.y);
}

Vector::operator QString() const
{
    return QString("Vector(" + QString::number(x) + ", " + QString::number(y) + ")");
}
