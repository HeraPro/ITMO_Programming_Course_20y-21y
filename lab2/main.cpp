#include "interface.h"
#include <fstream>

using std::ifstream;

int main(){
    ifstream fin("input.txt");
    string input;
    int n;
    fin >> n;
    getline(fin, input);
    Polynom first (input);

    return 0;
}
