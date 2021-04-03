#include "interface.h"
#include <fstream>

using std::ifstream;

int main(){
    ifstream fin("input.txt");
    string input;
    int n;
    fin >> n;
    getline(fin, input);
    getline(fin, input);
    Polynom first (input);
    Polynom second (input);
    getline(fin, input);
    Polynom third (input);
    bool check = first == second;
    bool check2 = first == third;
    bool check3 = third != second;
    int a;
    a = first[0];
    cout << a << '\n' << check << ' ' << check2 << ' ' << check3;
    third *= second;
    return 0;
}
