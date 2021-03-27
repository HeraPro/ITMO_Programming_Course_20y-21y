#ifndef PROGA_LAB2_INTERFACE_H
#define PROGA_LAB2_INTERFACE_H

#include <iostream>
#include <vector>
#include <algorithm>
using std::vector, std::pair, std::sort;

bool cmp (const pair<double, int>& a, const pair<double, int>& b);

class Polynomial{
private:
vector<pair<double, int>> monomials;  //coefficient, power
public:
    Polynomial(const vector<pair<double, int>>& tmp);
    Polynomial(const double& tmp);
    Polynomial (const Polynomial& tmp) = default;
    Polynomial () = default;
    ~Polynomial() = default;
    Polynomial& operator = (const Polynomial& tmp) = default;

    Polynomial& operator += (const Polynomial& tmp);
    Polynomial& operator -= (const Polynomial& tmp);
    Polynomial& operator *= (const Polynomial& factor);
    Polynomial& operator /= (const double& divider);

    bool operator == (const Polynomial& tmp) const;
    bool operator != (const Polynomial& tmp) const;

    const Polynomial operator - () const;
    const Polynomial operator / (const double& divider) const;

    pair<double, int>& operator [] (int index);
    pair<double, int> operator [] (int index) const;

    friend std::ostream& operator << (std::ostream& out, const Polynomial& tmp);
};

const Polynomial operator + (const Polynomial& tmp1, const Polynomial& tmp2);
const Polynomial operator - (const Polynomial& tmp1, const Polynomial& tmp2);
const Polynomial operator * (const Polynomial& tmp1, const Polynomial& tmp2);
std::istream& operator >> (std::istream& in, Polynomial& tmp);
std::ostream& operator << (std::ostream& out, const Polynomial& tmp);
std::ostream& operator << (std::ostream& out, const pair<double, int>& tmp);



#endif