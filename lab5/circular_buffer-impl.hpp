#pragma once

#include "memory"


template <typename Data>
CircularBuffer<Data>::CircularBuffer(size_t capacity)
    : capacity_{capacity}, size_{0} {
    start_ = head = alloc_traits::allocate(array, capacity_);
    for (size_t i = 0; i < capacity_; ++i){
        start_[i] = 0;
    }
//  head = new Data[capacity];
 // start_ = head;
}

template <typename Data>
Data& CircularBuffer<Data>::operator[](size_t i) {
  return head[index(i)];
}

template <typename Data>
const Data& CircularBuffer<Data>::operator[](size_t i) const {
  return head[index(i)];
}

template <typename Data>
CircularBuffer<Data>::CircularBuffer(const CircularBuffer& buffer):
    size_{buffer.size_},
    capacity_{buffer.capacity_}{
    start_ = head = alloc_traits::allocate(array, capacity_);
    for (size_t i = 0; i < size_; i++) {
        operator[](i) = buffer[i];
     }
}

template <typename Data>
CircularBuffer<Data>::~CircularBuffer() {
//  for (size_t i = 0; i < capacity_; ++i) {
//    head[i].~T();
//  }
  alloc_traits::destroy(array, head);

}

template <typename Data>
CircularBuffer<Data>& CircularBuffer<Data>::operator=(const CircularBuffer& buffer) {
    size_ = buffer.size_;
    capacity_ = buffer.capacity_;
    alloc_traits::destroy(array, head);
    head = alloc_traits::allocate(array, capacity_);
    start_ = (buffer.start_ - buffer.head) + head;
      for (size_t i = 0; i < size_; ++i) {
          operator[](i) = buffer[i];
      }
  return *this;
}

template <typename Data>
Data& CircularBuffer<Data>::front() {
  return operator[](0);
}

template <typename Data>
const Data& CircularBuffer<Data>::front() const {
  return operator[](0);
}

template <typename Data>
Data& CircularBuffer<Data>::back() {
  return operator[](size_ - 1);
}

template <typename Data>
const Data& CircularBuffer<Data>::back() const {
  return operator[](size_ - 1);
}

template <typename Data>
void CircularBuffer<Data>::push_back(const Data& element) {
  if (size_ != capacity_) {
    ++size_;
  } else {
    ++start_;
  }
  back() = element;
}

template <typename Data>
const Data CircularBuffer<Data>::pop_back() {
  const auto& return_value = back();
  --size_;
  return return_value;
}

template <typename Data>
void CircularBuffer<Data>::push_front(const Data& element) {
  if (size_ != capacity_) {
    ++size_;
  }

  // decrement start circularly
  if (start_ != head) {
    --start_;
  } else {
    start_ = head + capacity_ - 1;
  }

  front() = element;
}

template <typename Data>
const Data CircularBuffer<Data>::pop_front() {
  const auto& return_value = front();
  --size_;

  // increment start_ circularly
  if (start_ - head == capacity_ - 1) {
    start_ = head;
  } else {
    ++start_;
  }

  return return_value;
}

template <typename Data>
void CircularBuffer<Data>::ChangeCapacity(size_t new_capacity) {
    if (capacity_ == new_capacity){ return; }
//    if (capacity_ > new_capacity){ size_ = capacity_ = new_capacity;}
    std::allocator<Data> tmp;
    Data *ptr;
    ptr = alloc_traits::allocate(tmp, new_capacity);
    const auto new_size = std::min(size_, new_capacity);
    for (size_t i = 0; i < new_size; ++i) {
        ptr[i] = operator[](i);
    }
    alloc_traits::destroy(array, head);
    array = tmp;
    size_ = new_size;
    capacity_ = new_capacity;
    head = start_ = ptr;

  /*auto new_array = new Data[new_capacity];
  const auto new_size = std::min(size_, new_capacity);
  for (size_t i = 0; i < new_size; i++) {
      new_array[i] = operator[](i);
  }
  delete[] head;
  size_ = new_size;
  capacity_ = new_capacity;
    head = start_ = new_array; */
}

// iterator
template <typename Data>
typename CircularBuffer<Data>::iterator& CircularBuffer<Data>::iterator::operator+=(
    size_t i) {
  cur_ = ptr_ + (cur_ - ptr_ + i) % capacity_;
  diff_from_start_ += i;
  return *this;
}

template <typename Data>
typename CircularBuffer<Data>::iterator&
CircularBuffer<Data>::iterator::operator++() {
  return *this += 1;
}

template <typename Data>
typename CircularBuffer<Data>::iterator const CircularBuffer<Data>::iterator::operator++(int) {
  auto return_iterator = *this;
  *this += 1;
  return return_iterator;
}

template <typename Data>
typename CircularBuffer<Data>::iterator CircularBuffer<Data>::iterator::operator+(
    size_t i) const {
  auto return_iterator = *this;
  return return_iterator += i;
}

template <typename Data>
typename CircularBuffer<Data>::iterator& CircularBuffer<Data>::iterator::operator-=(
    size_t i) {
  cur_ = ptr_ + (cur_ - ptr_ - i + capacity_) % capacity_;
  diff_from_start_ -= i;
  return *this;
}

template <typename Data>
typename CircularBuffer<Data>::iterator&
CircularBuffer<Data>::iterator::operator--() {
  return *this -= 1;
}

template <typename Data>
typename CircularBuffer<Data>::iterator const CircularBuffer<Data>::iterator::operator--(int) {
  auto return_iterator = *this;
  *this -= 1;
  return return_iterator;
}

template <typename Data>
typename CircularBuffer<Data>::iterator CircularBuffer<Data>::iterator::operator-(
    size_t i) const {
  auto return_iterator = *this;
  return return_iterator -= i;
}

template <typename Data>
Data& CircularBuffer<Data>::iterator::operator*() {
  return *cur_;
}

template <typename Data>
Data& CircularBuffer<Data>::iterator::operator[](size_t i) {
  return *(*this + i);
}

template <typename T>
auto CircularBuffer<T>::iterator::operator-(const iterator& iterator) const {
  return diff_from_start_ - iterator.diff_from_start_;
}

template <typename Data>
const bool CircularBuffer<Data>::iterator::operator==(const iterator& iterator) const {
  return diff_from_start_ == iterator.diff_from_start_;
}

template <typename Data>
const bool CircularBuffer<Data>::iterator::operator!=(const iterator& iterator) const {
  return *this != iterator;
}

template <typename Data>
const bool CircularBuffer<Data>::iterator::operator<(const iterator& iterator) const {
  return (iterator - *this) > 0;
}

template <typename Data>
const bool CircularBuffer<Data>::iterator::operator>(const iterator& iterator) const {
  return iterator < *this;
}


