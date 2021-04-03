#pragma once
#include "interface.h"
#include <iostream>

Polynom::Polynom(string &_polynom){
    if (_polynom.length() == 0) return;
    for (int i = 0; i < _polynom.length(); ++i){
        if (_polynom[i] == ' ') {
            _polynom.erase(i, 1);
            --i;
        }
    }
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
    for (int i = 0; i != tmp.length();){
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
    if (polynom != tmp.polynom) return false;
    return true;
}

bool Polynom::operator != (const Polynom &tmp) const{
    return !(operator == (tmp));
}

Polynom &Polynom::operator += (const Polynom &tmp){
    for (auto i : tmp.polynom){
        polynom[i.first] += i.second;
    }
    return *this;
}

Polynom &Polynom::operator -= (const Polynom &tmp){
    for (auto i : tmp.polynom){
        polynom[i.first] -= i.second;
    }
    return *this;
}

Polynom &Polynom::operator *= (const Polynom &tmp){  // fixed
    Polynom swap;
    for (auto i : polynom){
        for (auto j : tmp.polynom){
            auto degree = 0;
            degree = i.first + j.first;
            swap.polynom[degree] += i.second * j.second;
        }
    }
    return *this = swap;
}

Polynom &Polynom::operator /= (const int &tmp){
    for (auto i : polynom){
        polynom[i.first] /= tmp;
    }
    return *this;
}

const Polynom Polynom::operator + (const Polynom &tmp) const{
    Polynom sum = *this;
    return sum += tmp;
}

const Polynom Polynom::operator - (const Polynom &tmp) const{
    Polynom diff = *this;
    return diff -= tmp;
}

const Polynom Polynom::operator * (const Polynom &tmp) const{
    Polynom multi = *this;
    return multi *= tmp;
}

const Polynom Polynom::operator / (const int &tmp) const{
    Polynom div = *this;
    return div /= tmp;
}

//    Polynom &operator ()++;

//    Polynom &operator ()--;

//    Polynom &operator ++();

//    Polynom &operator --();

Polynom Polynom::operator - (){ // fixed
    Polynom tmp;
    for (auto i : polynom){
        tmp.polynom[i.first] = -(i.second);
    }
    return tmp;
}

std::ostream &operator << (std::ostream &out, const Polynom &tmp){ // fixed
    for (auto i: tmp.polynom)
        std::cout << i.first << ' ' << i.second << '\n';
    return out;
}

std::istream &operator >> (std::istream &in, Polynom &tmp){ // fixed
    cout << "Enter degree/coeff";
    int k;
    char i;
    while(std::cin >> i && std::cin >> k)
        if (i == '\n') return in;
        else tmp.polynom[i - '0'] = k;
    return in;
}

int Polynom::operator [] (const int i){
    return polynom[i];
}

