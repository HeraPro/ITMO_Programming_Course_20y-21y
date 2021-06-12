#include <iostream>
#include <algorithm>

#include "circular_buffer.hpp"

template <typename Buffer>
void PrintBuffer(Buffer&& buffer) {
  std::cout << "  ";
  for (auto&& i : buffer) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

template <typename Buffer>
void PrintReverseBuffer(Buffer&& buffer) {
  std::cout << "  ";
  for (auto it = buffer.rbegin(); it != buffer.rend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename Buffer>
void InsertSomeElements(Buffer&& buffer) {
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.pop_front();
    buffer.pop_front();
    buffer.push_back(4);
    buffer.push_front(5);
    buffer.push_front(6);
    buffer.push_front(7);
}

void TestIteratorsForPrint() {
  std::cout << "Testing (-reverse)Iterators..." << std::endl;
  size_t capacity = 4;
  std::allocator<int> alloc; //testing with "own" alloc
  CircularBuffer<int32_t> buffer(capacity, alloc);
  InsertSomeElements(buffer);
  PrintBuffer(buffer);
  PrintReverseBuffer(buffer);
}

void TestIteratorsSTLAlgorithms() {
  std::cout << "Testing with some STL algorithms..." << std::endl;
  size_t capacity = 4;
  CircularBuffer<int32_t> buffer(capacity);
  InsertSomeElements(buffer);
  std::cout << "  Original buffer:" << std::endl;
  PrintBuffer(buffer);
  std::cout << "  Testing on std::sort: " << std::endl;
  std::sort(buffer.begin(), buffer.end());
  PrintBuffer(buffer);
  std::cout << "  Performing right-rotate using std::rotate: " << std::endl;
  std::rotate(buffer.rbegin(), buffer.rbegin() + 1, buffer.rend());
  PrintBuffer(buffer);
}

void TestChangeCapacity() {
  std::cout << "Testing ChangeCapacity..." << std::endl;
  size_t capacity = 4;
  CircularBuffer<int32_t> buffer(capacity);
  InsertSomeElements(buffer);
  std::cout << "  capacity = " << capacity << ": " << std::endl;
  PrintBuffer(buffer);

  capacity = 3;
  buffer.ChangeCapacity(capacity);
  std::cout << "  new decreased capacity = " << capacity << ": " << std::endl;
  PrintBuffer(buffer);

  capacity = 9;
  buffer.ChangeCapacity(capacity);
  std::cout << "  new increased capacity = " << capacity << ": " << std::endl;
  PrintBuffer(buffer);
}

int main() {
  TestIteratorsForPrint();
  std::cout << std::endl;
  TestChangeCapacity();
  std::cout << std::endl;
  TestIteratorsSTLAlgorithms();

    return 0;
}
