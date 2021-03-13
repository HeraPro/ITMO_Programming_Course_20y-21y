#include "interface.h"

//Point
double Point::DistanceBetween(const Point &A) const {
    return sqrt((A.x - x) * (A.x - x) + (A.y - y) * (A.y - y));
}


double Point::GetX() const {
    return x;
}


double Point::GetY() const {
    return y;
}

//BrokenLine
double BrokenLine::GetPerimeter() const {
    double perimeter = 0;
    for (int i = 0; i < size - 1; ++i){
        perimeter += points[i].DistanceBetween(points[i + 1]);
    }
    return perimeter;
}


//ClosedBrokenLine
ClosedBrokenLine::ClosedBrokenLine(const vector<Point> &tmp) :BrokenLine(tmp) {
    Point ab(points[0].GetX() - points[size - 1].GetX(), points[0].GetY() - points[size - 1].GetY());
    Point bc(points[1].GetX() - points[0].GetX(), points[1].GetY() - points[0].GetY());
    Point da(points[size - 1].GetX() - points[size - 2].GetX(), points[size - 1].GetY() - points[size - 2].GetY());
    if (ab.GetX() * bc.GetY() - ab.GetY() * bc.GetX() == 0 || ab.GetX() * da.GetY() - ab.GetY() * da.GetX() == 0){
        cout << "incorrect data entered" << endl;
    }
}
double ClosedBrokenLine::GetPerimeter() const {
    double perimeter = BrokenLine::GetPerimeter();
    return perimeter + points[0].DistanceBetween(points[size - 1]);
}

//Polygon
double Polygon::GetPerimeter() const {
    return ClosedBrokenLine::GetPerimeter();
}

double Polygon::GetSquare() const {
    double square = 0;
    const Point& fixed = points[0];
    for (int32_t i = 1; i < size - 1; ++i) {
        Point ab(points[i].GetX() - points[0].GetX(), points[i].GetY() - points[0].GetY());
        Point bc(points[i + 1].GetX() - points[0].GetX(), points[i + 1].GetY() - points[0].GetY());
        square += std::abs(ab.GetX() * bc.GetY() - ab.GetY() * bc.GetX()) / 2;
    }
    return square;
}

//Triangle
double Triangle::GetPerimeter() const {
    return Polygon::GetPerimeter();
}

double Triangle::GetSquare() const {
    Point ab(points[1].GetX() - points[0].GetX(), points[1].GetY() - points[0].GetY());
    Point bc(points[2].GetX() - points[0].GetX(), points[2].GetY() - points[0].GetY());
    return std::abs(ab.GetX() * bc.GetY() - ab.GetY() * bc.GetX()) / 2;
}

//Trapezoid
double Trapezoid::GetPerimeter() const {
    return Polygon::GetPerimeter();
}

double Trapezoid::GetSquare() const {
    return Polygon::GetSquare();
}

//RegularPolygon

double RegularPolygon::GetPerimeter() const {
    return size * side_length;
}

double RegularPolygon::GetSquare() const {
    const double pi = M_PI;
    const double R = side_length / 2 / std::sin(pi / size);
    const double r = R * std::cos(pi / size);

    return GetPerimeter() * r / 2;
}


