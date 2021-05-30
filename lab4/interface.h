#pragma once

namespace myspace {

    template <typename N>
    bool more (N first, N second){
        return second > first;
    }

    template <typename N>
    bool positive_numbers (N x){
        return x > 0;
    }
    template <typename N>
    bool negative_numbers (N x){
        return x < 0;
    }

    template <typename N>
    bool equality (N first, N second){
        return first == second;
    }

    template <typename N>
    bool less (N first, N second){
        return first < second;
    }

    template <typename N>
    bool greater_or_eq (N first, N second){
        return first >= second;
    }

    template <typename N>
    bool less_or_eq (N first, N second){
        return first <= second;
    }


    template <typename InputIterator, typename Function>
    bool all_of(InputIterator begin, InputIterator end, Function func){
        for (; begin != end; ++begin){
            if (!func(*begin))
                return false;
        }
        return true;
    }

    template <typename InputIterator, typename Function>
    bool any_of(InputIterator begin, InputIterator end, Function func){
        for (; begin != end; ++begin) {
            if (func(*begin))
                return true;
        }
        return false;
    }

    template <typename InputIterator, typename Function>
    bool none_of(InputIterator begin, InputIterator end, Function func) {
        return !myspace::any_of(begin, end, func);
    }

    template <typename InputIterator, typename Function>
    bool one_of(InputIterator begin, InputIterator end, Function func){
        for (bool exist = false; begin != end; ++begin){
            if (func(*begin) && !exist)
                exist = true;
            else if (func(*begin) && exist)
                return false;
        }
        return true;
    }

    template <typename InputIterator, typename Function>
    bool is_sorted(InputIterator begin, InputIterator end, Function func){
        for (InputIterator back = begin++; begin != end; ++begin, ++back) {
            if (!func(*back, *begin))
                return false;
        }
        return true;

    }

    template <typename InputIterator, typename Function>
    bool is_partitioned(InputIterator begin, InputIterator end, Function func){
        for (; begin != end; ++begin) {
            if (!func(*begin))
                break;
        }
        for (; begin != end; ++begin) {
            if (func(*begin))
                return false;
        }
        return true;
    }

    template <typename InputIterator, typename Element>
    InputIterator find_not(InputIterator begin, InputIterator end, Element elem){
        for (; begin != end; ++begin){
            if (*begin != elem)
                return begin;
        }
        return end;
    }

    template <typename BidirectionalIterator, typename Element>
    BidirectionalIterator find_backward(BidirectionalIterator begin, BidirectionalIterator end, Element elem){
        for (; end != begin;) {
            --end;
            if (*end == elem)
                return end;
        }
        return begin;

    }

    template <typename RandomAccessIterator, typename Function> //ama right with naming iterators? check out later
    bool is_palindrome(RandomAccessIterator begin, RandomAccessIterator end, Function func){
        for (; begin != end; ){
            --end;
            if (begin == end) //have to work on moving iter with even and uneven combs
                return true;
            if (!func(*begin, *end))
                return false;
            ++begin;
        }
        return false;
    }

}
