#pragma once
#include <iostream>
#include <cmath>
#include <vector>


using std::vector, std::cout, std::endl;

class Point{
public:
    Point(double x, double y) : x{x}, y{y} {} //constructor
   Point(const Point& tmp): x(tmp.x), y(tmp.y) {}             //copy constructor
   Point& operator = (const Point& tmp){                      //assignment operator
        x = tmp.x;
        y = tmp.y;
        return *this;
   }

    double DistanceBetween(const Point& A) const;
    double GetX() const;
    double GetY() const;
private:
    double x;
    double y;
};


class BrokenLine{
public:
    explicit BrokenLine(const vector<Point>& tmp) : size(tmp.size()), points(tmp) { //constructor
        if (size < 3) cout << "incorrect data entered" << endl;
        for (int i = 0; i < size - 2; ++i){
            Point ab(points[i + 1].GetX() - points[i].GetX(), points[i + 1].GetY() - points[i].GetY());
            Point bc(points[i + 2].GetX() - points[i + 1].GetX(), points[i + 2].GetY() - points[i + 1].GetY());
            if (ab.GetX() * bc.GetY() - ab.GetY() * bc.GetX() == 0){
                cout << "incorrect data entered" << endl;
            }
        }
    }
//    BrokenLine(const BrokenLine& tmp) : points(tmp.points), size(tmp.size) {}
//    BrokenLine& operator = (const BrokenLine& tmp){//        points = tmp.points;
//        size = tmp.size;
//        return *this;
//    }
    virtual double GetPerimeter() const;
protected:
    vector<Point> points;
    size_t size;
};


class ClosedBrokenLine: public BrokenLine{            //protected(reinterpret cast); public(static cast)     -------
public:
    explicit ClosedBrokenLine(const vector<Point>& tmp); //constructor
    double GetPerimeter() const override;
};


class Polygon: protected ClosedBrokenLine {
public:
    explicit Polygon(const vector<Point>& tmp) :ClosedBrokenLine(tmp) { //constructor
        double prev_vector_product = 0;
        for (int32_t i = 0; i < size; ++i) {
            const Point ab(points[(i + 1) % size].GetX() - points[i].GetX(), points[(i + 1) % size].GetY() - points[i].GetY());
            const Point bc(points[(i + 2) % size].GetX() - points[(i + 1) % size].GetX(), points[(i + 2) % size].GetY() - points[(i + 1) % size].GetY());
            const auto cur_vector_product = ab.GetX() * bc.GetY() - ab.GetY() * bc.GetX();
            if (cur_vector_product * prev_vector_product < 0) {
                cout << "it isn't a Polygon, incorrect data entered" << endl;
            }
            prev_vector_product = cur_vector_product;
        }
    }
    double GetPerimeter() const override;
    virtual double GetSquare() const;
};


class Triangle final: public Polygon{
public:
    explicit Triangle(const vector<Point>& tmp) : Polygon(tmp) {  //constructor
        if (size != 3) {
            cout << "it isn't a Triangle, incorrect data entered" << endl;
        }
    }
    double GetPerimeter() const override;
    double GetSquare() const override;
};


class Trapezoid: public Polygon{
public:
    explicit Trapezoid(const vector<Point>& tmp) : Polygon(tmp) {   //constructor
        if (size != 4) {
            cout << "it isn't a Trapezoid, incorrect data entered" << endl;
        }                                     // make [0,1] and [2, 3] are parallel
        Point ab(points[2].GetX() - points[1].GetX(), points[2].GetY() - points[1].GetY());
        Point bc(points[3].GetX() - points[0].GetX(), points[3].GetY() - points[0].GetY());
        if (ab.GetX() * bc.GetY() - ab.GetY() * bc.GetX() == 0){
            const auto save = points[0];
            points[0] = points[1];
            points[1] = points[2];
            points[2] = points[3];
            points[3] = save;
        }
    }
    double GetPerimeter() const override;
    double GetSquare() const override;
};


class RegularPolygon : public Polygon {
public:
    explicit RegularPolygon(const std::vector<Point>& tmp):Polygon(tmp), side_length(points[0].DistanceBetween(points[1])) {
        for (int i = 1; i < size; ++i) {
            const double cur_length = points[i].DistanceBetween(points[(i + 1) % size]);
            if (side_length != cur_length) {
                cout << "it isn't a regular polygon, incorrect data entered";
            }
        }
    }
    double GetPerimeter() const override;
    double GetSquare() const override;
private:
    double side_length;
};