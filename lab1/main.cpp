#include "interface.h"

#include <iostream>
int main(){
    Point S(-3, -2);
    Point S1(3, 4);
    Point S3(6, 10);
    std::vector<Point> a = {S, S1, S3};
    BrokenLine SSS(a);
    ClosedBrokenLine AAA(a);
    vector<BrokenLine*> array = {&SSS, reinterpret_cast<BrokenLine*>(&AAA)};
    for (auto element : array)
        cout << element->GetPerimeter() << endl;
}