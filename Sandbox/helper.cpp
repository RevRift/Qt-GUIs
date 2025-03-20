#include "helper.h"
#include <QDebug>

bool operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}
Point operator+(const Point& a, const Point& b) {
  return Point(a.x + b.x, a.y + b.y);
}
Point operator-(const Point& a, const Point& b) {
  return Point(a.x - b.x, a.y - b.y);
}
bool operator==(const Circle& c, const Circle& d) {
    return c.ctr == d.ctr && c.r == d.r;
}

QDebug operator<<(QDebug debug, const Point& p) {
    return debug << "(" << p.x << "," << p.y << ")";
}
QDebug operator<<(QDebug debug, const Circle& c) {
    return debug << "centre:" << c.ctr << ", radius:" << c.r;
}
QDebug operator<<(QDebug debug, const Node& n) {
    return debug << n.pos << ", path length:" << n.path_length << ", heuristic:" << n.heuristic << ", cw:" << n.cw
        << ", circle: " << *n.circle << ", prev:" << (n.prev == nullptr ? Point(0, 0) : n.prev->pos);
}

double dist(const Point& a, const Point& b) {
  return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
};

double arg(const Point& p, bool debug) { // returns angle to positive x-axis in the interval [0, 2pi)
    if (debug) qDebug() << "finding arg of:" << p;
    if (p.x > 0.0 && p.y >= 0) return std::atan(std::abs(p.y/p.x));
    if (p.x < 0.0 && p.y >= 0) return M_PI - std::atan(std::abs(p.y/p.x));
    if (p.x < 0.0 && p.y <= 0) return M_PI + std::atan(std::abs(p.y/p.x));
    if (p.x > 0.0 && p.y <= 0) return 2*M_PI - std::atan(std::abs(p.y/p.x));
    if (/*p.x == 0 &&*/ p.y > 0) return M_PI_2;
    if (/*p.x == 0 &&*/ p.y < 0) return 3 * M_PI_2;
    return 0.0;
};

bool Equals(double actual, double expected)
{
    return actual == expected;
}

bool EqualsWithDelta(double actual, double expected, double max_error)
{
    return std::abs(actual - expected) <= max_error;
}
