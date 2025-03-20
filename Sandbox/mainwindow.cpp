#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * make testing functionality (drawing lines, points, arcs) works
 * test basic functions
 * test more complex functions
 * add node.cw logic to remove cusped edges
 * refactor with const references
 * favour this code over the code in "Shortest_path"
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(this);
    view->setRenderHint(QPainter::Antialiasing);

    view->show();
    view->setFocus();
    setCentralWidget(view);

    pen.setColor(Qt::green); pen.setWidth(4);
    circle_colour = Qt::yellow;
    point_colour = Qt::blue;
    axes_colour = Qt::red;
    scale = 100;

    do_tests();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_line(const Point& p1, const Point& p2, QPen _pen = QPen()) {
    scene->addLine(QLineF(scale * p1.x, scale * -p1.y, scale * p2.x, scale * -p2.y), _pen);
}
void MainWindow::add_line(const Node& n1, const Node& n2, QPen _pen = QPen()) {
    add_line(n1.pos, n2.pos, _pen);
}
void MainWindow::add_arc(const Node& n1, const Node& n2, QPen _pen = QPen()) {
    const Circle& c = *n1.circle;
    double alpha = arg(n1.pos - n1.circle->ctr), beta = arg(n2.pos - n1.circle->ctr);
    AnglePairs ranges = (n1.cw)
            ? (alpha >= beta) ? AnglePairs{{beta, alpha}} : AnglePairs{{beta, 2*M_PI}, {-1e-16, alpha}}
            : (beta >= alpha) ? AnglePairs{{alpha, beta}} : AnglePairs{{alpha, 2*M_PI}, {-1e-16, beta}};
    for (auto [start_angle, end_angle] : ranges) {
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(QRectF(scale * (c.ctr.x - c.r), scale * (-c.ctr.y - c.r), scale * c.r * 2, scale * c.r * 2));
        start_angle *= 16 * 360/(2*M_PI);
        end_angle *= 16 * 360/(2*M_PI);
        item->setStartAngle(start_angle);
        item->setSpanAngle(end_angle - start_angle);
        item->setPen(_pen);
        scene->addItem(item);
    }
}

void MainWindow::add_circle(const Point& ctr, double r, QColor colour = Qt::white) {
    scene->addEllipse(QRectF(scale * (ctr.x - r), scale * (-ctr.y - r), scale * r * 2, scale * r * 2), QPen(), QBrush(colour));
}

void MainWindow::set_up_grid_lines(double min_x, double max_x, double min_y, double max_y, int padding = 1)
{
    min_x -= padding, max_x += padding;
    min_y -= padding, max_y += padding;
    for (int i = min_x; i <= max_x; ++i)
        add_line({(double)i, min_y}, {(double)i, max_y});
    for (int i = min_y; i <= max_y; ++i)
        add_line({min_x, (double)i}, {max_x, (double)i});
    add_line({min_x, 0}, {max_x, 0}, axes_colour);
    add_line({0, min_y}, {0, max_y}, axes_colour);
}
void MainWindow::display_test(const Point& start, const Point& end, const std::vector<Circle>& circles)
{
   int min_x = std::min({0.0, start.x, end.x})-1, max_x = std::max({0.0, start.x, end.x})+1,
       min_y = std::min({0.0, start.y, end.y})-1, max_y = std::max({0.0, start.y, end.y})+1;
   for (const Circle& c : circles) {
       min_x = std::min(min_x, int(std::floor(c.ctr.x - c.r))), max_x = std::max(max_x, int(std::ceil(c.ctr.x + c.r)));
       min_y = std::min(min_y, int(std::floor(c.ctr.y - c.r))), max_y = std::max(max_y,  int(std::ceil(c.ctr.y + c.r)));
       add_circle(c.ctr, c.r, circle_colour);
   }
   for (const Point& p : {start, end}) add_circle(p, 0.05, point_colour);
   set_up_grid_lines(min_x, max_x, min_y, max_y);
   view->setScene(scene);
}

bool MainWindow::point_is_valid(Point p, const std::vector<Circle>& circles){
    return std::all_of(circles.begin(), circles.end(), [&](const Circle& c){
        return dist(p, c.ctr) >= c.r;
    });
};

bool MainWindow::created_loop(Node node){
    for (const Node* p = node.prev; p != nullptr; p = p->prev)
        if (p->pos == node.pos) return true;
    return false;
};

bool MainWindow::line_is_valid(const Point& p1, const Point& p2, const Circle& c1, const Circle& c2, const std::vector<Circle>& circles, unsigned debug = 0){
    if (debug) qDebug() << "checking line from" << p1 << "to" << p2;
    if (p1 == p2) { if (debug) qDebug() << "points were identical"; return true; }
    double a  = p2.x - p1.x, b = p2.y - p1.y;
    if (debug >= 2) qDebug() << "a:" << a << "b:" << b;
    return std::all_of(circles.begin(), circles.end(), [&](const Circle& circle){
        if (debug) qDebug() << "checking if it collides with circle:" << circle;
        for (const Circle& c_ : {c1, c2}) if (c_ == circle) return true; // &c_ shouldn't equal nullptr
        double c = circle.ctr.x - p1.x, d = circle.ctr.y - p1.y, k = (a*c + b*d) / (a*a + b*b);
        if (debug >= 2) qDebug() << "c:" << c << "d:" << d << "k:" << k;
        double x = (0 <= k && k <= 1)
                ? std::abs(a*d - b*c) / std::sqrt(a*a + b*b)
                : std::min(dist(p1, circle.ctr), dist(p2, circle.ctr));
        if (debug) qDebug() << "x:" << x << "radius:" << circle.r;
        return x >= circle.r;
    });
};

bool MainWindow::arc_is_valid(const Node& n1, const Node& n2, const std::vector<Circle>& circles, unsigned debug = 0) {
    if (debug) qDebug() << "checking if the arc from node:" << n1 << "to" << n2.pos << "is valid";
    if (n1.pos == n2.pos) return true;
    double alpha = arg(n1.pos - n1.circle->ctr), beta = arg(n2.pos - n1.circle->ctr);
    if (debug >= 2) qDebug() << "alpha:" << alpha << "beta:" << beta;
    AnglePairs ranges = (n1.cw)
            ? (alpha >= beta) ? AnglePairs{{beta, alpha}} : AnglePairs{{beta, 2*M_PI}, {-1e-16, alpha}} // try 0 instead of -1e-16 or another bigger number
            : (beta >= alpha) ? AnglePairs{{alpha, beta}} : AnglePairs{{alpha, 2*M_PI}, {-1e-16, beta}};
    for (const Circle& c : circles) {
        if (debug) qDebug() << "checking if it collides with circle:" << c;
        if (c == *n1.circle) continue;
        double d = dist(n1.circle->ctr, c.ctr), r = n1.circle->r;
        if (debug >= 2) qDebug() << "r:" << r << "d:" << d << "c.r:" << c.r;
        if (d <= std::abs(r - c.r) || d >= r + c.r) continue;
        double theta = arg(c.ctr - n1.circle->ctr), phi = std::acos((r*r + d*d - c.r*c.r) / (2*r*d));
        if (debug >= 2) qDebug() << "theta:" << theta << "phi:" << phi;
        for (double angle : {theta + phi, theta - phi}) {
            angle = std::fmod(angle + 2*M_PI, 2*M_PI);
            for (auto& [start_angle, end_angle] : ranges) {
                if (debug) qDebug() << "start angle:" << start_angle << "angle" << angle << "end angle:" << end_angle;
                if (start_angle < angle && angle < end_angle) return false;
            }
        }
    }
    return true;
};

void MainWindow::find_next_nodes(const Node& node, const Node& end_node, const std::vector<Circle>& circles, unsigned debug = 0, int depth = 1) {
    if (debug) qDebug() << "searching for a path for node:" << node;
    std::vector<Path> paths;
    std::pair<Circle *, int> key{const_cast<Circle *>(node.circle), node.cw};
    auto it = paths_from_circles.find(key);
    if (it == paths_from_circles.end()) {
        if (debug) qDebug() << "path from circle wasn't in the map";
        for (const Circle& c : circles) {
            if (debug >= 2) qDebug() << "investigating circle:" << c;
            if (c == *node.circle) continue;
            double d = dist(node.circle->ctr, c.ctr), theta = arg(c.ctr - node.circle->ctr), r = node.circle->r;
            if (debug >= 2) qDebug() << "d:" << d << "theta:" << theta;
            std::vector<std::tuple<double, double, bool>> angle_pairs;
            if (r + c.r <= d) { // find internal bitangents and tangents(where circles touch)
                double alpha = std::acos((r + c.r) / d);
                if (debug >= 2) qDebug() << "alpha:" << alpha;
                if (node.cw) angle_pairs.push_back({theta + alpha, theta + alpha + M_PI, true});
                if (!node.cw || (r == 0 && c.r != 0)) angle_pairs.push_back({theta - alpha, theta - alpha + M_PI, (r != 0)});
            }
            if (r != 0 && std::abs(r - c.r) < d) { // find external bitangents
                double beta = std::acos((r - c.r) / d);
                if (debug >= 2) qDebug() << "beta:" << beta;
                if (node.cw) angle_pairs.push_back({theta + beta, theta + beta, false});
                else angle_pairs.push_back({theta - beta, theta - beta, false});
            }
            for (const auto& [angle1, angle2, changesRotation] : angle_pairs) { // validate paths
                if (debug >= 2) qDebug() << "angle1:" << angle1 << ", angle2:" << angle2 << ", changes rotation:" << changesRotation;
                Point start_pos = node.circle->ctr + Point(r * std::cos(angle1), r * std::sin(angle1)),
                      end_pos = c.ctr + Point(c.r * std::cos(angle2), c.r * std::sin(angle2));
                if (line_is_valid(start_pos, end_pos, *node.circle, c, circles, 0)) {
                    if (debug) qDebug() << "path was valid";
                    paths.push_back({start_pos, end_pos, dist(start_pos, end_pos), dist(end_pos, end_node.pos/* should just be end*/),
                                    &c, node.cw, (node.cw ^ changesRotation)});
                } else {
                    if (debug) qDebug() << "path wasn't valid";
                }
                if (debug) qDebug();
            }
        }
        paths_from_circles.insert({key, paths}); // refactor this
        it = paths_from_circles.find(key);
    } else {
        if (debug) qDebug() << "path from circle was in the map";
    }
    std::vector<Node> nodes;
    for (const Path& path : it->second) { // create arc and check arc is valid, if so add it to nodes
        double phi = (node.circle->r == 0) ? 0.0 : arg(path.start_pos - node.circle->ctr) - arg(node.pos - node.circle->ctr);
        if (phi < 0) phi += 2*M_PI; if (node.cw /* && phi != 0 */) phi = 2*M_PI - phi;
        double arc_length = phi * node.circle->r;
        Node n1 {path.start_pos, node.path_length + arc_length, node.path_length + arc_length + dist(path.start_pos, end_node.pos), node.cw, node.circle, &node},
             n2 {path.end_pos, n1.path_length + path.length, n1.path_length + path.length + path.dist_to_end, path.end_cw, path.end_circle, nullptr};
        if (debug >= 2) qDebug() << "arc length" << arc_length;
        if (arc_is_valid(node, n1, circles, 0)) { // what if n1 has already been passed (i.e. an earlier path has already tried this route and failed)
            if (debug) qDebug() << "arc was valid";
            add_arc(node, n1, pen); add_line(n1, n2, pen);
            for (const Node& n : {n1, n2}) add_circle(n.pos, 0.05, Qt::gray);
            visited_nodes.push_back(n1); nodes.push_back(n2);
        } else {
            if (debug) qDebug() << "arc wasn't valid";
        }
        if (debug) qDebug();
    }
    if (--depth > 0) for (const auto& n : nodes) find_next_nodes(n, end_node, circles, debug, depth);
}

void MainWindow::do_tests()
{
    const double max_error = 1e-8;
    Point a,b;
    std::vector<Circle> c;
    double actual;

//    a = { 1, 1 };
//    b = { 9, 9 };
//    c = {
//    { 0, 0, 0.162875 },
//    { 0, 1, 0.352399 },
//    { 0, 2, 0.536426 },
//    { 0, 3, 0.430062 },
//    { 0, 4, 0.3106 },
//    { 0, 5, 0.526689 },
//    { 0, 6, 0.56848 },
//    { 0, 7, 0.583306 },
//    { 0, 8, 0.199401 },
//    { 0, 9, 0.190163 },
//    { 0, 10, 0.496312 },
//    { 1, 0, 0.794503 },
//    { 1, 2, 0.251076 },
//    { 1, 3, 0.716956 },
//    { 1, 4, 0.525058 },
//    { 1, 5, 0.193072 },
//    { 1, 6, 0.426112 },
//    { 1, 7, 0.237577 },
//    { 1, 8, 0.590785 },
//    { 1, 9, 0.380313 },
//    { 1, 10, 0.489955 },
//    { 2, 0, 0.531981 },
//    { 2, 1, 0.384474 },
//    { 2, 2, 0.29231 },
//    { 2, 3, 0.392367 },
//    { 2, 4, 0.500586 },
//    { 2, 5, 0.628159 },
//    { 2, 6, 0.436075 },
//    { 2, 7, 0.675493 },
//    { 2, 8, 0.391326 },
//    { 2, 9, 0.493831 },
//    { 2, 10, 0.252058 },
//    { 3, 0, 0.57627 },
//    { 3, 1, 0.310903 },
//    { 3, 2, 0.605751 },
//    { 3, 3, 0.406157 },
//    { 3, 4, 0.638791 },
//    { 3, 5, 0.398329 },
//    { 3, 6, 0.516773 },
//    { 3, 7, 0.364334 },
//    { 3, 8, 0.302254 },
//    { 3, 9, 0.588904 },
//    { 3, 10, 0.699331 },
//    { 4, 0, 0.652984 },
//    { 4, 1, 0.580129 },
//    { 4, 2, 0.146748 },
//    { 4, 3, 0.641685 },
//    { 4, 4, 0.158159 },
//    { 4, 5, 0.496153 },
//    { 4, 6, 0.294012 },
//    { 4, 7, 0.690078 },
//    { 4, 8, 0.5668 },
//    { 4, 9, 0.392792 },
//    { 4, 10, 0.514897 },
//    { 5, 0, 0.127403 },
//    { 5, 1, 0.503068 },
//    { 5, 2, 0.477784 },
//    { 5, 3, 0.262593 },
//    { 5, 4, 0.329032 },
//    { 5, 5, 0.462934 },
//    { 5, 6, 0.524399 },
//    { 5, 7, 0.547288 },
//    { 5, 8, 0.386409 },
//    { 5, 9, 0.200125 },
//    { 5, 10, 0.491025 },
//    { 6, 0, 0.333342 },
//    { 6, 1, 0.339046 },
//    { 6, 2, 0.366566 },
//    { 6, 3, 0.475729 },
//    { 6, 4, 0.823775 },
//    { 6, 5, 0.60554 },
//    { 6, 6, 0.860442 },
//    { 6, 7, 0.37139 },
//    { 6, 8, 0.56018 },
//    { 6, 9, 0.75424 },
//    { 6, 10, 0.484995 },
//    { 7, 0, 0.337052 },
//    { 7, 1, 0.416191 },
//    { 7, 2, 0.604189 },
//    { 7, 3, 0.271194 },
//    { 7, 4, 0.65111 },
//    { 7, 5, 0.512637 },
//    { 7, 6, 0.796956 },
//    { 7, 7, 0.667399 },
//    { 7, 8, 0.561956 },
//    { 7, 9, 0.332489 },
//    { 7, 10, 0.730007 },
//    { 8, 0, 0.649132 },
//    { 8, 1, 0.401713 },
//    { 8, 2, 0.263748 },
//    { 8, 3, 0.592208 },
//    { 8, 4, 0.352105 },
//    { 8, 5, 0.278676 },
//    { 8, 6, 0.548382 },
//    { 8, 7, 0.592111 },
//    { 8, 8, 0.281601 },
//    { 8, 9, 0.514096 },
//    { 8, 10, 0.665443 },
//    { 9, 0, 0.219636 },
//    { 9, 1, 0.501355 },
//    { 9, 2, 0.438918 },
//    { 9, 3, 0.526489 },
//    { 9, 4, 0.531778 },
//    { 9, 5, 0.355053 },
//    { 9, 6, 0.416108 },
//    { 9, 7, 0.211436 },
//    { 9, 8, 0.60296 },
//    { 9, 10, 0.623569 },
//    { 10, 0, 0.404193 },
//    { 10, 1, 0.522966 },
//    { 10, 2, 0.430659 },
//    { 10, 3, 0.571068 },
//    { 10, 4, 0.527629 },
//    { 10, 5, 0.487614 },
//    { 10, 6, 0.236933 },
//    { 10, 7, 0.483111 },
//    { 10, 8, 0.569641 },
//    { 10, 9, 0.681657 },
//    { 10, 10, 0.356473 },
//    };

    a = {-2.5, 3.0};   b = {-2.5, -5};
    c = { {-3.5, 0.0, 1.0}, {0.0, 0.0, 2.5}, {1.5, 2.0, 0.5}, {3.5, 1.0, 1.0}, {3.5, -1.7, 1.2} };

    std::srand(std::time(nullptr));
    int x = std::rand() % c.size(), y = std::rand() % c.size();
    double alpha = std::rand() % 360, beta = std::rand() % 360;
    Circle start_circle(c[x]), end_circle(c[y]); c.push_back(end_circle);
    Node n1{start_circle.ctr + Point(start_circle.r * std::cos(alpha * 2*M_PI / 360), start_circle.r * std::sin(alpha * 2*M_PI/360)),
           0, 0, 1, &start_circle, nullptr};
    Node n2{end_circle.ctr + Point(end_circle.r * std::cos(beta * 2*M_PI / 360), end_circle.r * std::sin(beta * 2*M_PI/360)),
           0, 0, -1, &end_circle, nullptr};
    display_test(n1.pos, n2.pos, c);
    find_next_nodes(n1, n2, c, 0, 2);

//    Circle c1(a, 0), c2(b, 0);
//    Node node_a{a, 0, 0, 1, &c1, nullptr},
//         node_b{b, 0, 0, 1, &c2, nullptr};
//    display_test(a, b, c);
//    find_next_nodes(node_a, node_b, c, 0);
}


