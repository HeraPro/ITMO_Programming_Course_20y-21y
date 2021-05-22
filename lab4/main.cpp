#include "interface.h"
#include <iostream>
#include <vector>

using namespace myspace;

int main () {
    std::vector <int> vec = {1, 2, 3, 3, -1, 1};

    std::cout << std::boolalpha;
    std::cout << "all_of - " << myspace::all_of(vec.begin(), vec.end(), positive_numbers<int>)  << '\n';
    std::cout << "any_of - " << myspace::any_of(vec.begin(), vec.end(), positive_numbers<int>) << '\n';
    std::cout << "none_of - " << myspace::none_of(vec.begin(), vec.end(), positive_numbers<int>) << '\n';
    std::cout << "one_of - " << one_of(vec.begin(), vec.end(), positive_numbers<int>) << '\n';
    std::cout << "is_sorted - " << myspace::is_sorted(vec.begin(), vec.end(), more<int>) << '\n';
    std::cout << "is_partitioned - " << myspace::is_partitioned(vec.begin(), vec.end(), negative_numbers<int>) << '\n';
    std::cout << "find_not - " << *find_not(vec.begin(), vec.end(), 1) << '\n';
    std::cout << "find_backward - " << *find_backward(vec.begin(), vec.end(), 2) << '\n';
    std::cout << "is_palindrome - " << is_palindrome(vec.begin(), vec.end(), equality<int>) << '\n';

    return 0;
}
