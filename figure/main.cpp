#include "Shapes.h"

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

    Shape* shapes[5];

    shapes[0] =
    new Circle(Point(0, 0), 5);

    shapes[1] =
    new Ellipse(Point(0, 0), 6, 3);

    shapes[2] =
    new Triangle(3, 4, 5);

    shapes[3] =
    new Rectangle(10, 5);

    shapes[4] =
    new Polygon("/Users/sashabuzinaevicloud.com/Downloads/granitsy-uchastka2.txt");

    int rectangle_count = 0;
    int circle_count = 0;
    int triangle_count = 0;
    int noise_count = 0;

    double total_area = 0;

    // Полиморфизм

    for (int i = 0; i < 5; i++) {

        show_info(shapes[i]);

        total_area +=
        shapes[i]->calc_area();


        if (dynamic_cast<Rectangle*>(
            shapes[i])) {

            rectangle_count++;
        }

        else if (dynamic_cast<Circle*>(
                 shapes[i])) {

            circle_count++;
        }

        else if (dynamic_cast<Triangle*>(
                 shapes[i])) {

            triangle_count++;
        }

        else {

            noise_count++;
        }
    }

    // txt

    ofstream result(
    "/Users/sashabuzinaevicloud.com/Downloads/result.txt");

    if (!result.is_open()) {

        cout << "Файл не открылся"
             << endl;

        return 0;
    }

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

    cout << "Total area = "
         << total_area
         << endl;


    for (int i = 0; i < 5; i++) {

        delete shapes[i];
    }

    return 0;
}
