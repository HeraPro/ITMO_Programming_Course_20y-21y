#include "interface.h"
#include <iostream>
using std::pair, std::vector, std::cout, std::endl;

int main(){
    vector <pair<double, int>> ss = {{-1.9, 4}, {-1.7, 2}, {2.2, 0}, {5, 1}};
    vector <pair<double, int>> sss = {{1.9, 4}, {1.9, 3}, {2.2, 1}, {2.2, 0}};
    Polynomial SS(ss);
    Polynomial SSS(sss);
    cout << (SS + SSS) << endl;
    cout << (SS - SSS) << endl;
    cout << (SS * SSS) << endl;
    cout << (SS / 10) << endl;
    cout << (SS == SSS) << endl;
    cout << (SS != SSS) << endl;
    cout << -SS << endl;
    cout << SS[2];
}
