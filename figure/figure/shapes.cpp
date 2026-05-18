
#include "shapes.h"

Point::Point(double ax, double ay) {
    x = ax;
    y = ay;
}

// ===== Circle =====

Circle::Circle(Point c, double r) {
    center = c;
    radius = r;
}

double Circle::calc_area() {
    return 3.14159 * radius * radius;
}

double Circle::calc_perimetr() {
    return 2 * 3.14159 * radius;
}

void Circle::name() {
    cout << "Circle" << endl;
}

// ===== Ellipse =====

Ellipse::Ellipse(Point c, double aa, double bb) {
    center = c;
    a = aa;
    b = bb;
}

double Ellipse::calc_area() {
    return 3.14159 * a * b;
}

double Ellipse::calc_perimetr() {
    return 2 * 3.14159 * sqrt((a * a + b * b) / 2);
}

void Ellipse::name() {
    cout << "Ellipse" << endl;
}

// ===== Triangle =====

Triangle::Triangle(double aa, double bb, double cc) {
    a = aa;
    b = bb;
    c = cc;
}

double Triangle::calc_perimetr() {
    return a + b + c;
}

double Triangle::calc_area() {

    double p = calc_perimetr() / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

void Triangle::name() {
    cout << "Triangle" << endl;
}

// ===== Rectangle =====

Rectangle::Rectangle(double w, double h) {
    width = w;
    height = h;
}

double Rectangle::calc_area() {
    return width * height;
}

double Rectangle::calc_perimetr() {
    return 2 * (width + height);
}

void Rectangle::name() {
    cout << "Rectangle" << endl;
}

// ===== Polygon =====

Polygon::Polygon() {}

Polygon::Polygon(const char* file_name) {

    ifstream file(file_name);

    double x, y;

    while (file >> x >> y) {
        points.push_back(Point(x, y));
    }

    file.close();
}

void Polygon::addPoint(Point p) {
    points.push_back(p);
}

double Polygon::calc_area() {

    double area = 0;

    size_t n = points.size();

    for (int i = 0; i < n; i++) {

        int j = (i + 1) % n;

        area += points[i].x * points[j].y;
        area -= points[j].x * points[i].y;
    }

    return abs(area) / 2.0;
}

double Polygon::calc_perimetr() {

    double perim = 0;

    size_t n = points.size();

    for (int i = 0; i < n; i++) {

        int j = (i + 1) % n;

        double dx = points[j].x - points[i].x;
        double dy = points[j].y - points[i].y;

        perim += sqrt(dx * dx + dy * dy);
    }

    return perim;
}

void Polygon::name() {
    cout << "Polygon" << endl;
}
