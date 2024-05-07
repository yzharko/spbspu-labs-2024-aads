#ifndef TASK_HPP
#define TASK_HPP
#include <iosfwd>
#include <string>
#include "iolists.hpp"

namespace sadofeva
{
  list_lists_t transformList(const input_list_t & list);
  unsigned long sumNumbersFromList(const numbers_list_t & list);
  unsigned long long sum(unsigned long long a, unsigned long long b);
}

#endif
