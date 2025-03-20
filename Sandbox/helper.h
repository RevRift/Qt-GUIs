#ifndef HELPER_H
#define HELPER_H
/************ debug **************/
#include <QDebug>
#include <cstdlib>
/*********************************/

#include <cmath>
#include <queue>
#include <list>
#include <map>
#include <utility>


using AnglePairs = std::vector<std::pair<double, double>>;

struct Point
{
 double x,y;

 Point() : x(0.0), y(0.0) {}
 Point(double x, double y) : x(x), y(y) {}
 ~Point() = default;
};

struct Circle
{
 Point ctr;
 double r;

 Circle() : ctr(), r(1.0) {}
 Circle(Point c, double r) : ctr(c), r(r) {}
 Circle(double cx, double cy, double r) : ctr(cx,cy), r(r) {}
};

struct Node {
    Point pos;
    double path_length, heuristic; // path length is the running length of the path ending at this node
    int cw; // stores 1 if the nodes path around the circle is clockwise, 0 if anticlockwise, -1 if neither and we should discard such nodes
    const Circle* circle;
    const Node* prev; // store all visited nodes in a vector
                     // to check if a path has visited a node, call "prev_node" recursively down the path
};
struct Path {
    Point start_pos, end_pos;
    double length, dist_to_end;
    const Circle* end_circle;
    int start_cw, end_cw;
};
struct CompareHeuristic {
  bool operator() (const Node& a, const Node& b) {
    return a.heuristic > b.heuristic;
  }
};

bool operator==(const Point& a, const Point& b);
Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
bool operator==(const Circle& c, const Circle& d);

QDebug operator<<(QDebug debug, const Point& p);
QDebug operator<<(QDebug debug, const Circle& c);
QDebug operator<<(QDebug debug, const Node& n);

double dist(const Point& a, const Point& b);
double arg(const Point& p, bool debug = false);

bool Equals(double actual, double expected);
bool EqualsWithDelta(double actual, double expected, double max_error);

#endif // HELPER_H

