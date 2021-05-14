#include <algorithm>
#include <array>
#include <iostream>
#include <random>

#include <catch2/catch.hpp>


//as Container you can use std::array, std::vector or std::deque
template <typename Container>
uint partition(Container &array, uint low, uint high) {
  auto pivot = high;
  auto firstHigh = low;

  for (size_t i = low; i < array.size(); ++i) {
    if (array[i] < array[pivot]) {
      std::swap(array[i], array[firstHigh]);
      ++firstHigh;
    }
  }
  std::swap(array[pivot], array[firstHigh]);

  return firstHigh;
}

template <typename Container>
void quicksort(Container &array, uint low, uint high) {
  if (low < high) {
    auto part = partition(array, low, high);
    quicksort(array, low, part - 1);
    quicksort(array, part + 1, high);
  }
}

template <typename Container> void quicksort(Container &array) {
  quicksort(array, 0, array.size() - 1);
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

  quicksort(array);

  printArray(array);

  CHECK(std::is_sorted(array.begin(), array.end()));
}