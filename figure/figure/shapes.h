
#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

class Point {
public:
    double x;
    double y;

    Point(double ax = 0, double ay = 0);
};

class Shape {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;

    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    Point center;
    double radius;

public:
    Circle(Point c, double r);

    double calc_area();
    double calc_perimetr();
    void name();
};

class Ellipse : public Shape {
private:
    Point center;
    double a;
    double b;

public:
    Ellipse(Point c, double aa, double bb);

    double calc_area();
    double calc_perimetr();
    void name();
};

class Triangle : public Shape {
private:
    double a;
    double b;
    double c;

public:
    Triangle(double aa, double bb, double cc);

    double calc_area();
    double calc_perimetr();
    void name();
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h);

    double calc_area();
    double calc_perimetr();
    void name();
};

class Polygon : public Shape {
private:
    vector<Point> points;

public:
    Polygon();
    Polygon(const char* file_name);

    void addPoint(Point p);

    double calc_area();
    double calc_perimetr();
    void name();
};

#endif
