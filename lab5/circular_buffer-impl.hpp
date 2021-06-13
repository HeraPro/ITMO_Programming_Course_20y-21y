#pragma once

#include <memory>

template<typename Data, typename Alloc>
CircularBuffer<Data, Alloc>::CircularBuffer(const size_t capacity):
        capacity_{capacity},
        size_{0},
        head(alloc_traits::allocate(alloc_, capacity)) {
    start_ = head;
    for (size_t i = 0; i < capacity_; ++i) {
        alloc_traits::construct(alloc_, head + i, 0);
        //head[i] = 0;
    }
//  head = new Data[capacity];
    // start_ = head;
}

/*template<typename Data, typename Alloc>
CircularBuffer<Data, Alloc>::CircularBuffer(const size_t capacity, Alloc &alloc):
        capacity_{capacity},
        size_{0} {
    start_ = head = alloc_.allocate(capacity_);
    for (size_t i = 0; i < capacity_; ++i) {
        alloc_.construct(head + i, 0);
        //head[i] = 0;
    }

//  head = new Data[capacity];
    // start_ = head;
}*/

template<typename Data, typename Alloc>
CircularBuffer<Data, Alloc>::CircularBuffer(const CircularBuffer &buffer): //fixed
        size_{buffer.size_},
        capacity_{buffer.capacity_} {
    alloc_traits::select_on_container_copy_construction(alloc_);
    head = alloc_traits::allocate(alloc_, capacity_);
    start_ = (buffer.start_ - buffer.head) + head;
    for (size_t i = 0; i < size_; ++i) {
        alloc_.construct(head +i, buffer.head[i]);
        //operator[](i) = buffer[i];
    }
}

template<typename Data, typename Alloc>
Data &CircularBuffer<Data, Alloc>::operator[](size_t i) {
    return head[index(i)];
}

template<typename Data, typename Alloc>
const Data &CircularBuffer<Data, Alloc>::operator[](size_t i) const {
    return head[index(i)];
}

template<typename Data, typename Alloc>
CircularBuffer<Data, Alloc>::~CircularBuffer() { //fixed for custom destroy
    for (size_t i = 0; i < capacity_; ++i) {
        alloc_traits::destroy(alloc_, head + i);
    }
    //std::destroy(begin(), end());
    alloc_traits::deallocate(alloc_, head, capacity_);
}

/*template<typename Data>
CircularBuffer<Data> &CircularBuffer<Data>::operator=(const CircularBuffer &buffer) { //rewrite
    if (capacity_ == buffer.capacity_){
        for (size_t i = 0; i < capacity_; i++) {
            operator[](i) = buffer[i];
        }
        return *this;
    }
    std::destroy(begin(), end()); //rewrite
    alloc_.deallocate(head, capacity_);
    size_ = buffer.size_;
    capacity_ = buffer.capacity_;
    head = alloc_.allocate(capacity_);
    start_ = (buffer.start_ - buffer.head) + head;
    for (size_t i = 0; i < size_; ++i) {
        operator[](i) = buffer[i];
    }
    return *this;
}*/

template<typename Data, typename Alloc>
Data &CircularBuffer<Data, Alloc>::front() {
    return operator[](0);
}

template<typename Data, typename Alloc>
const Data &CircularBuffer<Data, Alloc>::front() const {
    return operator[](0);
}

template<typename Data, typename Alloc>
Data &CircularBuffer<Data, Alloc>::back() {
    return operator[](size_ - 1);
}

template<typename Data, typename Alloc>
const Data &CircularBuffer<Data, Alloc>::back() const {
    return operator[](size_ - 1);
}

template<typename Data, typename Alloc>
void CircularBuffer<Data, Alloc>::push_back(const Data &element) { //fixed
    if (size_ != capacity_) {
        ++size_;
    } else {
        ++start_;
    }
    alloc_traits::construct(alloc_, &back(), element); //construct from allocator
    //back() = element;
}

template<typename Data, typename Alloc>
const Data CircularBuffer<Data, Alloc>::pop_back() {
    const auto &return_value = back();
    --size_;
    return return_value;
}

template<typename Data, typename Alloc>
void CircularBuffer<Data, Alloc>::push_front(const Data &element) { //fixed
    if (size_ != capacity_) {
        ++size_;
    }

    // decrement start circularly
    if (start_ != head) {
        --start_;
    } else {
        start_ = head + capacity_ - 1;
    }
    alloc_traits::construct(alloc_, &front(), element);
}

template<typename Data, typename Alloc>
const Data CircularBuffer<Data, Alloc>::pop_front() {
    const auto &return_value = front();
    --size_;

    // increment start_ circularly
    if (start_ - head == capacity_ - 1) {
        start_ = head;
    } else {
        ++start_;
    }

    return return_value;
}

template<typename Data, typename Alloc>
void CircularBuffer<Data, Alloc>::ChangeCapacity(size_t new_capacity) { //fixed
    if (capacity_ == new_capacity) { return; }
    alloc_traits::select_on_container_copy_construction(alloc_);
    Data *ptr;
    ptr = alloc_traits::allocate(alloc_, new_capacity);
    const auto new_size = std::min(size_, new_capacity);
    for (size_t i = 0; i < new_size; ++i) {
        alloc_traits::construct(alloc_, ptr + i, operator[](i)); //including custom
        //(ptr[i] = operator[](i);
    }
    for (size_t i = 0; i < capacity_; ++i) {
        alloc_traits::destroy(alloc_, head + i);
    }
    //std::destroy(begin(), end());
    alloc_.deallocate(head, capacity_);
    size_ = new_size;
    capacity_ = new_capacity;
    head = start_ = ptr;

/*    if (capacity_ == new_capacity) { return; }
//    if (capacity_ > new_capacity){ size_ = capacity_ = new_capacity;}
    Data *ptr;
    ptr = alloc_.allocate(new_capacity);
    const auto new_size = std::min(size_, new_capacity);
    for (size_t i = 0; i < new_size; ++i) {
        ptr[i] = operator[](i);
    }
    std::destroy(begin(), end());
    alloc_.deallocate(head, capacity_);
    size_ = new_size;
    capacity_ = new_capacity;
    head = start_ = ptr;*/
}

// iterator
template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator &CircularBuffer<Data, Alloc>::iterator::operator+=(size_t i) {
    cur_ = ptr_ + (cur_ - ptr_ + i) % capacity_;
    diff_from_start_ += i;
    return *this;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator &
CircularBuffer<Data, Alloc>::iterator::operator++() {
    return *this += 1;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator const CircularBuffer<Data, Alloc>::iterator::operator++(int) {
    auto return_iterator = *this;
    *this += 1;
    return return_iterator;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator CircularBuffer<Data, Alloc>::iterator::operator+(size_t i) const {
    auto return_iterator = *this;
    return return_iterator += i;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator &CircularBuffer<Data, Alloc>::iterator::operator-=(
        size_t i) {
    cur_ = ptr_ + (cur_ - ptr_ - i + capacity_) % capacity_;
    diff_from_start_ -= i;
    return *this;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator &
CircularBuffer<Data, Alloc>::iterator::operator--() {
    return *this -= 1;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator const CircularBuffer<Data, Alloc>::iterator::operator--(int) {
    auto return_iterator = *this;
    *this -= 1;
    return return_iterator;
}

template<typename Data, typename Alloc>
typename CircularBuffer<Data, Alloc>::iterator CircularBuffer<Data, Alloc>::iterator::operator-(size_t i) const {
    auto return_iterator = *this;
    return return_iterator -= i;
}

template<typename Data, typename Alloc>
Data &CircularBuffer<Data, Alloc>::iterator::operator*() {
    return *cur_;
}

template<typename Data, typename Alloc>
Data &CircularBuffer<Data, Alloc>::iterator::operator[](size_t i) {
    return *(*this + i);
}

template<typename Data, typename Alloc>
auto CircularBuffer<Data, Alloc>::iterator::operator-(const iterator &iterator) const {
    return diff_from_start_ - iterator.diff_from_start_;
}

template<typename Data, typename Alloc>
const bool CircularBuffer<Data, Alloc>::iterator::operator==(const iterator &iterator) const {
    return diff_from_start_ == iterator.diff_from_start_;
}

template<typename Data, typename Alloc>
const bool CircularBuffer<Data, Alloc>::iterator::operator!=(const iterator &iterator) const {
    return !(*this == iterator);
}

template<typename Data, typename Alloc>
const bool CircularBuffer<Data, Alloc>::iterator::operator<(const iterator &iterator) const {
    return (iterator - *this) > 0;
}

template<typename Data, typename Alloc>
const bool CircularBuffer<Data, Alloc>::iterator::operator>(const iterator &iterator) const {
    return iterator < *this;
}


