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
    bool equality (N first, N second){
        return first == second;
    }

    template <typename N>
    bool less (N first, N second){
        return first < second;
    }

    template <typename N>
    bool more_or_eq (N first, N second){
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
    bool any_of(Function func, InputIterator begin, InputIterator end){
        for (; begin != end; ++begin) {
            if (func(*begin))
                return true;
        }
        return false;
    }

    template <typename InputIterator, typename Function>
    bool none_of(InputIterator begin, InputIterator end, Function func) {
        return !any_of(begin, end, func);
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
        for (InputIterator back = begin++; begin != end; ++begin) {
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
    Element find_not(InputIterator begin, InputIterator end, Element elem){
        for (; begin != end; ++begin){
            if (*begin != elem)
                return *begin;
        }
    }

    template <typename BidirectedIterator, typename Element>
    BidirectedIterator find_backward(BidirectedIterator begin, BidirectedIterator end, Element elem){
        --end; --begin;
        for (; end != begin; --end)
            if(*end == elem)
                return end;

    }

    template <typename BidirectedIterator, typename Function> //ama right with naming iterators? check out later
    bool is_palindrome(BidirectedIterator begin, BidirectedIterator end, Function func){
        --end;
        for (; begin != end; ){
            if (!func(*begin, *end))
                return false;
            --end;
            if (begin == end || begin == end - 1) //have to work on moving iter with even and uneven combs
                return true;
            else ++begin;
        }

    }

}
