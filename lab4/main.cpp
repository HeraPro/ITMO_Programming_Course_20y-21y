#include "interface.h"
#include <iostream>
#include <vector>

using namespace myspace;

int main () {
    std::vector <int> vec = {1, 2, 3, 4, 5};

    std::cout << "all_of - " << (myspace::all_of(vec.begin(), vec.end(), positive_numbers<int>) ? "true" : "false") << '\n';
    std::cout << "any_of - " << (myspace::any_of(vec.begin(), vec.end(), positive_numbers<int>) ? "true" : "false") << '\n';
    std::cout << "none_of - " << (myspace::none_of(vec.begin(), vec.end(), positive_numbers<int>) ? "true" : "false") << '\n';
    std::cout << "one_of - " << (myspace::one_of(vec.begin(), vec.end(), positive_numbers<int>) ? "true" : "false") << '\n';
    std::cout << "is_sorted - " << (myspace::is_sorted(vec.begin(), vec.end(), cmp<int>) ? "true" : "false") << '\n';
    std::cout << "is_partitioned - " << (myspace::is_partitioned(vec.begin(), vec.end(), positive_numbers<int>) ? "true" : "false") << '\n';
    std::cout << "find_not - " << find_not(vec.begin(), vec.end(), 1) << '\n';
    std::cout << "find_backward - " << find_backward(vec.begin(), vec.end(), 5) << '\n';
    std::cout << "is_palindrome - " << (is_palindrome(vec.begin(), vec.end(), positive_numbers<int>) ? "true" : "false") << '\n';

    return 0;
}


