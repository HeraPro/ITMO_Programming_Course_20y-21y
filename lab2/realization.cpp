#include "interface.h"
//    Polynomial(const Polynomial& tmp) : monomials(tmp.monomials) {}// copy
//    Polynomial& operator = (const Polynomial& tmp) {                     //assignment =
//        monomials = tmp.monomials;
//        return *this;
//    }
bool cmp(const pair<double, int> &a, const pair<double, int> &b) {
    return a.second > b.second;
}

// IN CLASS

Polynomial::Polynomial(const vector<pair<double, int>> &tmp) : monomials(tmp) {   //constructor
    sort(monomials.begin(), monomials.end(), cmp);
}

Polynomial::Polynomial(const double &tmp) : monomials(1, {tmp, 0}) {} // constructor from number

Polynomial &Polynomial::operator+=(const Polynomial &tmp) {                  // +=
    vector<pair<double, int>> result;
    int count1 = 0;
    int count2 = 0;
    int len1 = this->monomials.size();
    int len2 = tmp.monomials.size();
    while (len1 && len2){
        if (this->monomials[count1].second > tmp.monomials[count2].second){
            result.emplace_back(this->monomials[count1]);
            ++count1;
            --len1;
        }
        else if (this->monomials[count1].second < tmp.monomials[count2].second){
            result.emplace_back(tmp.monomials[count2]);
            ++count2;
            --len2;
        }
        else {
            double first_el = this->monomials[count1].first + tmp.monomials[count2].first;
            int sec_el = this->monomials[count1].second;
            if (first_el != 0)
                result.emplace_back(first_el, sec_el);
            ++count1, ++count2;
            --len1, --len2;
        }
    }
    if (len1 == 0) {
        for (int i = count2; i < tmp.monomials.size(); ++i)
            result.emplace_back(tmp.monomials[i]);
    }
    else {
        for (int i = count1; i < this->monomials.size(); ++i)
            result.emplace_back(this->monomials[i]);
    }
    this->monomials = result;
    return *this;
}

bool Polynomial::operator==(const Polynomial &tmp) const {    // ==
    return this->monomials == tmp.monomials;
}

bool Polynomial::operator!=(const Polynomial &tmp) const {     // !=
    return this->monomials != tmp.monomials;
}

const Polynomial Polynomial::operator-() const {      // -(unary)
    vector<pair<double, int>> result;
    for (auto i : this->monomials)
        result.emplace_back(-(i.first), i.second);
    return Polynomial(result);
}

Polynomial &Polynomial::operator-=(const Polynomial &tmp) {             // -=
    vector<pair<double, int>> result;
    int count1 = 0;
    int count2 = 0;
    int len1 = this->monomials.size();
    int len2 = tmp.monomials.size();
    while (len1 && len2){
        if (this->monomials[count1].second > tmp.monomials[count2].second){
            result.emplace_back(this->monomials[count1]);
            ++count1;
            --len1;
        }
        else if (this->monomials[count1].second < tmp.monomials[count2].second){
            result.emplace_back(-(tmp.monomials[count2].first), tmp.monomials[count2].second);
            ++count2;
            --len2;
        }
        else {
            double first_el = this->monomials[count1].first - tmp.monomials[count2].first;
            int sec_el = this->monomials[count1].second;
            if (first_el != 0)
                result.emplace_back(first_el, sec_el);
            ++count1, ++count2;
            --len1, --len2;
        }
    }
    if (len1 == 0) {
        for (int i = count2; i < tmp.monomials.size(); ++i)
            result.emplace_back(-(tmp.monomials[count2].first), tmp.monomials[count2].second);
    }
    else {
        for (int i = count1; i < this->monomials.size(); ++i)
            result.emplace_back(this->monomials[i]);
    }
    this->monomials = result;
    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &factor) {                      // *
    vector<pair<double, int>> this_copy = this->monomials;
    this->monomials = {{0, 0}};
    if (factor.monomials.size() == 1 && factor.monomials[0].first == 0 && factor.monomials[0].second == 0) return *this;
    vector<pair<double, int>> partial_product = {{0,0}};
    for (auto i : factor.monomials){
        for (auto j : this_copy){
            partial_product.emplace_back(j.first * i.first, j.second + i.second);
        }
        *this += partial_product;
        partial_product.clear();
    }
    return *this;
}

Polynomial &Polynomial::operator/=(const double &divider) {               // /=
    if (divider == 0) {
        std::cout << "cannot be divided by 0";
        exit(1);
    }
    for (int i = 0 ; i < this->monomials.size(); ++i)
        this->monomials[i].first /= divider;
    return *this;
}

const Polynomial Polynomial::operator/(const double &divider) const {      // /
    if (divider == 0) {
        std::cout << "cannot be divided by 0";
        exit(1);
    }
    Polynomial quotient = *this;
    return quotient /= divider;
}

pair<double, int> &Polynomial::operator[](int index) {             // []
    return this->monomials[index];
}

pair<double, int> Polynomial::operator[](int index) const {       // const []
    return this->monomials[index];
}


// OUT OF CLASS


const Polynomial operator+(const Polynomial &tmp1, const Polynomial &tmp2) {  // +
    Polynomial sum = tmp1;
    return sum += tmp2;
}

const Polynomial operator-(const Polynomial &tmp1, const Polynomial &tmp2) {  // -
    Polynomial difference = tmp1;
    return difference += tmp2;
}

const Polynomial operator*(const Polynomial &tmp1, const Polynomial &tmp2) {  // *
    Polynomial product = tmp1;
    return product *= tmp2;
}

std::istream &operator>>(std::istream &in, Polynomial &tmp) {     // >>
    std::cout << "enter number of monomials x:" << std::endl;
    int num_of_monomials;
    while((!(in >> num_of_monomials)) || num_of_monomials < 0) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "incorrect data, enter number of monomials again" << std::endl;
        in >> num_of_monomials;
    }
    std::cout << "enter x pairs of numbers (coefficient, power)" << std::endl;
    vector<pair<double, int>> monomials;
    while (num_of_monomials--) {
        double a;
        int b;
        in >> a >> b;
        if (in.fail()){
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            ++num_of_monomials;
            std::cout << "incorrect data, enter this pair again" << std::endl;
            continue;
        }
        monomials.emplace_back(a, b);
    }
    tmp = monomials;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &tmp) {// <<
    if (tmp.monomials[0].second != 0)
        out << tmp.monomials[0].first << "x^" << tmp.monomials[0].second;
    else
        out << tmp.monomials[0].first;
    for (int i = 1; i < tmp.monomials.size(); ++i){
        if (tmp.monomials[i].second != 0) {
            if (tmp.monomials[i].first > 0)
                out << " + " << tmp.monomials[i].first << "x^" << tmp.monomials[i].second;
            else
                out << " - " << -tmp.monomials[i].first << "x^" << tmp.monomials[i].second;
        }
        else {
            if (tmp.monomials[i].first > 0)
                out << " + " << tmp.monomials[i].first;
            else
                out << " - " << -tmp.monomials[i].first;
        }
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const pair<double, int> &tmp) {
    if (tmp.second != 0)
        out << tmp.first << "x^" << tmp.second;
    else
        out << tmp.first;
    return out;
}





