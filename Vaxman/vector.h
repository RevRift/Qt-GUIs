#ifndef VECTOR_H
#define VECTOR_H

/*
 * Description: created for easy addition of positions and directions
*/

#include <QString>

struct Vector
{
    int x, y;

    Vector();

    Vector(int x, int y);

    Vector operator + (const Vector &other);

    Vector operator += (const Vector &other);

    Vector operator - (const Vector &other);

    Vector operator -= (const Vector &other);

    Vector operator * (int multiplier);

    Vector operator *= (int multiplier);

    bool operator == (const Vector &other);

    bool operator != (const Vector &other);

    operator QString() const;
};

#endif // VECTOR_H
