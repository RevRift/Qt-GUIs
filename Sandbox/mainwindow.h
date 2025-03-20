#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "helper.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QThread>
#include <QGraphicsEllipseItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_line(const Point& p1, const Point& p2, QPen _pen);
    void add_line(const Node& p1, const Node& p2, QPen _pen);
    void add_arc(const Node& n1, const Node& n2, QPen _pen);
    void add_circle(const Point& p, double width, QColor colour);
    void set_up_grid_lines(double min_x, double max_x, double min_y, double max_y, int padding);
    void display_test(const Point& start, const Point& end, const std::vector<Circle>& circles);

    bool created_loop(Node node);
    bool point_is_valid(Point p, const std::vector<Circle>& circles);
    bool line_is_valid(const Point& p1, const Point& p2, const Circle& c1, const Circle& c2, const std::vector<Circle>& circles, unsigned debug);
    bool arc_is_valid(const Node& n1, const Node& n2, const std::vector<Circle>& circles, unsigned debug);

    void find_next_nodes(const Node& node, const Node& end_node, const std::vector<Circle>& circles, unsigned debug, int depth);
    void do_tests();

private:
    Ui::MainWindow *ui;

    QGraphicsView* view;
    QGraphicsScene* scene;
    int scale;
    QPen pen;
    QColor circle_colour, point_colour, axes_colour;
    std::list<Node> visited_nodes;
    std::map<std::pair<Circle *, int>, std::vector<Path>> paths_from_circles;
};
#endif // MAINWINDOW_H

