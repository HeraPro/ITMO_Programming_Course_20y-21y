#include "interface.h"

template <typename N>
bool myspace::cmp (N first, N second) {
    return second > first;
}

template <typename N>
bool myspace::positive_numbers (N x) {
    return x > 0;
}

template <typename T, typename Function>
bool myspace::all_of (const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter) {
        if (!func(*iter)) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Function>
bool myspace::any_of (const T  &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter) {
        if (func(*iter)) {
            return true;
        }
    }
    return false;
}

template <typename T, typename Function>
bool myspace::none_of (const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter) {
        if (func(*iter)) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Function>
bool myspace::one_of (const T &begin, const T &end, Function func) {
    int count = 0;
    for (T iter = begin; iter != end; ++iter) {
        if (func(*iter)) {
            ++count;
        }
    }
    return count == 1;
}


template <typename T, typename Function>
bool myspace::is_sorted (const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter) {
        if (func(*iter, *(iter - 1))) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Function>
bool myspace::is_partitioned (T first, T last, Function func) {
    for (; first != last; ++first) {
        if (!func(*first))
            break;
    }
    for (; first != last; ++first) {
        if (func(*first))
            return false;
    }
    return true;
}

template <typename T, typename Element>
Element myspace::find_not (const T &begin, const T &end, Element elem) {
    for (T iter = begin; iter != end; ++iter) {
        if (*iter != elem) {
            return *iter;
        }
    }
    return *end;
}

template <typename T, typename Element>
Element myspace::find_backward (const T &begin, const T &end, Element elem) {
    for (T iter = end - 1; iter != begin; --iter) {
        if (elem == *iter) {
            return *iter;
        }
    }
    return *end;

}

template <typename T, typename Function>
bool myspace::is_palindrome(const T &begin, const T &end, Function function){
    T start, finish;
    for (start = begin, finish = end - 1;
         start != end && finish != begin;
         start++, finish--) {
        if (*start != *finish) {
            return false;
        }
    }
    return true;
}

