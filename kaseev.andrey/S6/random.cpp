#include <algorithm>
#include <random>
#include "random.hpp"

int kaseev::generateRandomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

float kaseev::generateRandomFloat(float min, float max) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<float> distribution(min, max);
  return distribution(generator);
}

template< typename T >
void kaseev::generateNumbers(std::forward_list< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, size_t size, bool isInt) {
  for (size_t i = 0; i < size; ++i)
  {
    if (isInt) {
      int num = generateRandomInt(0, 100);
      singleList.push_front(num);
      doubleList.push_back(num);
      deq.push_back(num);
    }
    else {
      float num = generateRandomFloat(0.0f, 100.0f);
      singleList.push_front(num);
      doubleList.push_back(num);
      deq.push_back(num);
    }
  }
  singleList.reverse();
}
