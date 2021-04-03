#pragma once
#include "interface.h"
#include <iostream>

Polynom::Polynom(string &_polynom): origin('(' + _polynom + ')'){
    if (_polynom.length() == 0) return;
    for (int i = 0; i < _polynom.length(); ++i){
        if (_polynom[i] == ' ') {
            _polynom.erase(i, 1);
            --i;
        }
    }
    size = _polynom.length();
    parser(_polynom);
    for (auto &i : polynom)
        std::cout << i.first << ' ' << i.second << '\n';
    std::cout << "--------------------" << '\n';
}

void Polynom::count_numbers(char *&ptr, int &i, int &input){
    bool sign = false;
    if (*ptr == '-'){
        sign = true;
        ++i; ++ptr;
    }
    else if (*ptr == '+'){
        ++i; ++ptr;
    }
    if (*ptr == 'x'){
        input = sign == 0 ? 1 : -1;
        return;
    }
    while (*ptr >= '0' && *ptr <= '9'){
        input = input * 10 + *ptr - '0';
        ++i; ++ptr;
    }
    if (sign){input = -input;}
}
void Polynom::parser(string &tmp) {
    char *ptr = &tmp[0];
    for (int i = 0; i != size;){
        int coeff = 0, degree = 0;
        count_numbers(ptr, i, coeff);
        if(*ptr == 'x'){
            ++i; ++ptr;
            if(*ptr == '^') {
                ++i; ++ptr;
                count_numbers(ptr, i, degree);
                if (coeff == -1 && degree % 2 == 0) coeff = 1;
                polynom[degree] += coeff;
                continue;
            }
            else{
                polynom[1] += coeff;
                ++i; ++ptr;
                continue;
            }
        }
        if (coeff != 0) polynom[0] += coeff;
    }
}

void Polynom::get_polynom(){
    cout << origin << '\n';
}

//Polynom &Polynom::operator = (const Polynom &tmp){
//    size = tmp.size;
//    polynom = tmp.polynom;
//    origin = tmp.origin;
//    return *this;
//}

Polynom &Polynom::operator = (string input){
    Polynom tmp (input);
    *this = tmp;
    return *this;
}

bool Polynom::operator == (const Polynom &tmp) const{
    if (size != tmp.size) return false;
    if (origin == tmp.origin) return true;
    else if (polynom != tmp.polynom) return false;
    return true;
}

bool Polynom::operator != (const Polynom &tmp) const{
    return !operator == (tmp);
}

Polynom &Polynom::operator += (const Polynom &tmp){
    origin += tmp.origin;
    for (auto i : tmp.polynom){
        polynom[i.first] += i.second;
    }
    size = polynom.size();
    return *this;
}

Polynom &Polynom::operator -= (const Polynom &tmp){
    origin += " - (" + tmp.origin + ')';
    for (auto i : tmp.polynom){
        polynom[i.first] -= i.second;  // not sure about UB
    }
    size = polynom.size();
    return *this;
}

Polynom &Polynom::operator *= (const Polynom &tmp){  // fixed
    origin += "(" + tmp.origin + ')';
    for (auto i : polynom){
        for (auto j : tmp.polynom){
            auto swap = 0;
            swap = i.first + j.first;
            polynom[i.first] = 0;
            polynom[swap] = i.second * j.second;
        }
    }
    size = polynom.size();
    return *this;
}

Polynom &Polynom::operator /= (const int &tmp){
    origin += " / " + to_string(tmp);
    for (auto i : polynom){
        polynom[i.first] /= tmp;
    }
    return *this;
}

Polynom &Polynom::operator + (const Polynom &tmp) const{
    Polynom sum = *this;
    return sum += tmp;
}

Polynom &Polynom::operator - (const Polynom &tmp) const{
    Polynom diff = *this;
    return diff -= tmp;
}

Polynom &Polynom::operator * (const Polynom &tmp) const{
    Polynom multi = *this;
    return multi *= tmp;
}

Polynom &Polynom::operator / (const int &tmp) const{
    Polynom div = *this;
    return div /= tmp;
}

//    Polynom &operator ()++;

//    Polynom &operator ()--;

//    Polynom &operator ++();

//    Polynom &operator --();

Polynom &Polynom::operator - (){
    for (auto i : polynom){
        polynom[i.first] = -(i.second);
    }
    return *this;
}

Polynom &Polynom::operator >> (Polynom &tmp){
    for (auto i : polynom){
        tmp.polynom[i.first] = i.second;
    }
    return *this;
}

Polynom &Polynom::operator << (const Polynom &tmp){
    for (auto i : tmp.polynom){
        polynom[i.first] = i.second;
    }
    return *this;
}

int &Polynom::operator [] (const int i){
    if (polynom[i] != 0) return polynom[i];
    else cout << "Not found" << '\n';
}

