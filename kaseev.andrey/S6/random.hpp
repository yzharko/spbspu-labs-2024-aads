#ifndef AADS_RANDOM_HPP
#define AADS_RANDOM_HPP

#include <forward_list>
#include <list>
#include <deque>

namespace kaseev {
  int generateRandomInt(int min, int max);
  float generateRandomFloat(float min, float max);
  template< typename T >
  void generateNumbers(std::forward_list< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, size_t size, bool isInt);
}

#endif
