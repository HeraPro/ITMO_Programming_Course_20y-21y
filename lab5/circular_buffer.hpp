#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>

template<typename Data, typename Alloc = std::allocator<Data>>
class CircularBuffer {
private:
    size_t size_ = 0;
    size_t capacity_ = 0;

    Data *head = nullptr;
    Data *start_ = nullptr;

    using alloc_traits = std::allocator_traits<Alloc>;
    Alloc alloc_;

    size_t index(size_t i) const { return (start_ - head + i) % capacity_; };

public:
    CircularBuffer() = default;
    explicit CircularBuffer(const size_t capacity);
//    CircularBuffer(const size_t capacity, const Alloc &alloc_); //for custom allocator
    CircularBuffer(const CircularBuffer &);
    // CircularBuffer(CircularBuffer&&);

    ~CircularBuffer();

//    CircularBuffer &operator=(const CircularBuffer &);
    // CircularBuffer& operator=(CircularBuffer&&);

    void push_front(const Data &);

    // void push_front(Data&&);
    void pop_front();

    void push_back(const Data &);

    // void push_back(Data&&);
    const Data pop_back();

    const Data &front() const;

    Data &front();

    const Data &back() const;

    Data &back();

    const Data &operator[](size_t i) const;

    Data &operator[](size_t i);

    void ChangeCapacity(size_t new_capacity);

    size_t size() const { return size_; }

    // random access iterator
    class iterator {
    private:
        Data *ptr_;
        size_t size_;
        size_t capacity_;
        Data *cur_;
        Data *start_;
        int64_t diff_from_start_;

    public:
        iterator(Data *ptr, Data *cur, /*size_t size,*/ size_t capacity, Data *start,
                 int64_t diff_from_start)
                : ptr_(ptr),
                  cur_(cur),
                //size_(size),
                  diff_from_start_(diff_from_start),
                  capacity_(capacity),
                  start_(start) {}

        iterator &operator=(const iterator &iterator) = default;

        iterator &operator+=(size_t);

        iterator &operator++();

        const iterator operator++(int);

        iterator operator+(size_t) const;

        iterator &operator-=(size_t);

        iterator &operator--();

        const iterator operator--(int);

        iterator operator-(size_t) const;

        Data &operator*();

        Data &operator[](size_t);

        auto operator-(const iterator &iterator) const;

        const bool operator==(const iterator &iterator) const;

        const bool operator!=(const iterator &iterator) const;

        const bool operator<(const iterator &iterator) const;

        const bool operator>(const iterator &iterator) const;

        // typedefs for iterator_traits
        typedef std::random_access_iterator_tag iterator_category;
        typedef decltype(std::declval<iterator>() -
                         std::declval<iterator>()) difference_type;
        typedef Data value_type;
        typedef Data* pointer;
        typedef Data& reference;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;

    iterator begin() const{
        return iterator(head, start_,/* size_,*/ capacity_, start_, 0);
    }

    iterator end() const{
        return iterator(head, head + index(size_), /*size_,*/ capacity_, start_, capacity_);
    }

    reverse_iterator rbegin() const{ return std::make_reverse_iterator(end()); }

    reverse_iterator rend() const{ return std::make_reverse_iterator(begin()); }

//  class Alloc{
//  public:
//      typedef Data value_type;
//      typedef Data* pointer;
//      typedef Data& reference;
//  };



};

#include "circular_buffer-impl.hpp"

