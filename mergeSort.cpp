#include <algorithm>
#include <array>
#include <iostream>
#include <random>

#include <catch2/catch.hpp>

//as Container you can use std::array, std::vector or std::deque
template <typename Container>
void merge(Container &array, uint begin, uint middle, uint end) {
  Container auxArray{array};

  auto beg = begin;
  auto mid = middle + 1;

  for (size_t i = begin; i <= end; ++i) {
    if (beg > middle) {
      array[i] = auxArray[mid++];
    } else if (mid > end) {
      array[i] = auxArray[beg++];
    } else if (auxArray[beg] < auxArray[mid]) {
      array[i] = auxArray[beg++];
    } else {
      array[i] = auxArray[mid++];
    }
  }
}

template <typename Container>
void sort(Container &array, uint begin, uint end) {
  if (begin >= end) {
    return;
  }
  auto middle = begin + (end - begin) / 2;

  sort(array, begin, middle);
  sort(array, middle + 1, end);
  merge(array, begin, middle, end);
}

template <typename Container> void mergeSort(Container &array) {
  sort(array, 0, array.size() - 1);
}

std::random_device seed;
std::mt19937 engine(seed());
std::uniform_int_distribution<> generator(1, 30);

TEST_CASE() {

  constexpr uint SizeArray{20};
  std::array<int, SizeArray> array;

  std::generate(array.begin(), array.end(), []() { return generator(engine); });

  auto printArray = [](const auto &array) {
    for (const auto &var : array) {
      std::cout << var << " ";
    }
    std::cout << std::endl;
  };

  printArray(array);

  mergeSort(array);

  printArray(array);

  CHECK(std::is_sorted(array.begin(), array.end()));
}