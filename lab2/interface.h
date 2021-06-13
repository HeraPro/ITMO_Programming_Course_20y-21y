#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using std::string, std::unordered_map, std::vector, std::cout, std::to_string;

class Polynom{
private:
    unordered_map <int, int> polynom;
public:
    explicit Polynom(string &_polynom);
    Polynom() = default;
    Polynom &operator = (const Polynom &tmp)&;
  //  Polynom &operator = (string);

    bool operator == (const Polynom &tmp) const; //bool?
    bool operator != (const Polynom &tmp) const;

    Polynom &operator += (const Polynom &tmp);
    Polynom &operator -= (const Polynom &tmp);
    Polynom &operator *= (const Polynom &tmp);
    Polynom &operator /= (const int &tmp);

    Polynom operator + (const Polynom &tmp) const;
    Polynom operator - (const Polynom &tmp) const;
    Polynom operator * (const Polynom &tmp) const;
    Polynom operator / (const int &tmp) const;

//    Polynom &operator ()++;
//    Polynom &operator ()--;
//    Polynom &operator ++();
//    Polynom &operator --();

    Polynom operator - ();

    int operator [] (int i);

    ~Polynom() = default;

    friend std::ostream& operator<< (std::ostream &o,const Polynom &tmp);
    friend std::istream& operator >> (std::istream &in, Polynom &tmp);

protected:
    static void count_numbers(char *&ptr, int &input, int &i);
    void parser(string &tmp);
};



