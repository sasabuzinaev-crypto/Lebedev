#include <iostream>
#include <fstream>
#include <vector>
#include "shapes.h"

using namespace std;

void show_info(Shape* shape) {
    shape->name();

    cout << "Area = "
         << shape->calc_area()
         << endl;

    cout << "Perimetr = "
         << shape->calc_perimetr()
         << endl;

    cout << "-------------------"
         << endl;
}

int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Circle(Point(0, 0), 5));
    shapes.push_back(new Ellipse(Point(0, 0), 6, 3));
    shapes.push_back(new Triangle(3, 4, 5));
    shapes.push_back(new Rectangle(10, 5));
    shapes.push_back(new Polygon("/Users/sashabuzinaevicloud.com/Downloads/granitsy-uchastka2.txt"));

    int rectangle_count = 0;
    int circle_count = 0;
    int triangle_count = 0;
    int noise_count = 0;

    double total_area = 0;

    for (Shape* shape : shapes) {

        show_info(shape);

        total_area += shape->calc_area();

        if (dynamic_cast<Rectangle*>(shape)) {
            rectangle_count++;
        }
        else if (dynamic_cast<Circle*>(shape)) {
            circle_count++;
        }
        else if (dynamic_cast<Triangle*>(shape)) {
            triangle_count++;
        }
        else {
            noise_count++;
        }
    }

    ofstream result("/Users/sashabuzinaevicloud.com/Downloads/result.txt");

    if (!result.is_open()) {
        cout << "Файл не открылся" << endl;
        for (Shape* shape : shapes) {
            delete shape;
        }
        return 0;
    }

    result << "Rectangle = " << rectangle_count << endl;
    result << "Circle = "    << circle_count    << endl;
    result << "Triangle = "  << triangle_count  << endl;
    result << "Noise = "     << noise_count     << endl;

    result.close();

    cout << "Total area = " << total_area << endl;

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
