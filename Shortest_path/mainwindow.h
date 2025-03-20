#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "helper.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QElapsedTimer>

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
    void add_line(const Node& n1, const Node& n2, QPen _pen);
    void add_arc(const Node& n1, const Node& n2, QPen _pen);
    void add_circle(const Point& p, double width, QColor colour);
    void set_up_grid_lines(double min_x, double max_x, double min_y, double max_y, int padding);
    void display_test(const Point& start, const Point& end, const std::vector<Circle>& circles);
    void display_answer(const Node& end_node);

    double shortest_path_length(const Point& start, const Point& end, std::vector<Circle> circles, bool debug, bool display);
    void do_test(const Point& a, const Point& b, const std::vector<Circle>& c, double ans, bool debug, bool display);
    void do_tests();

private:
    Ui::MainWindow *ui;

    QGraphicsView* view;
    QGraphicsScene* scene;
    int scale;
    QPen path_pen, answer_pen, axes_pen;
    QColor circle_colour, point_colour, start_colour, end_colour;
    std::vector<Node> visited_nodes;
};
#endif // MAINWINDOW_H
