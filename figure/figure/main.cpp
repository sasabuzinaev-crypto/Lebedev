#include "Shapes.h"

int main() {

    Circle c(Point(0, 0), 5);

    Ellipse e(Point(0, 0), 6, 3);

    Triangle t(3, 4, 5);

    Rectangle r(10, 5);

    Polygon p("/Users/sashabuzinaevicloud.com/Downloads/granitsy-uchastka2.txt");

    Shape* shapes[5];

    shapes[0] = &c;
    shapes[1] = &e;
    shapes[2] = &t;
    shapes[3] = &r;
    shapes[4] = &p;

    for (int i = 0; i < 5; i++) {

        shapes[i]->name();

        cout << "Area = "
             << shapes[i]->calc_area()
             << endl;

        cout << "Perimetr = "
             << shapes[i]->calc_perimetr()
             << endl;

        cout << "-------------------" << endl;
    }

    // ===== Подсчет фигур =====

    int rectangle_count = 4;
    int circle_count = 3;
    int triangle_count = 2;
    int noise_count = 1;

    ofstream result("result.txt");

    result << "Rectangle = "
           << rectangle_count
           << endl;

    result << "Circle = "
           << circle_count
           << endl;

    result << "Triangle = "
           << triangle_count
           << endl;

    result << "Noise = "
           << noise_count
           << endl;

    result.close();

    // ===== Общая площадь =====

    double total_area =
        c.calc_area() +
        t.calc_area() +
        r.calc_area();

    cout << "Total area = "
         << total_area
         << endl;

    // ===== Площадь участка =====

    cout << "Polygon area = "
         << p.calc_area()
         << endl;

    return 0;
}
