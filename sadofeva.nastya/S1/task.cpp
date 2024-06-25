#include <limits>
#include <stdexcept>
#include "task.hpp"

<<<<<<< HEAD
//namespace sadofeva
//{
<<<<<<< HEAD
unsigned long long sum1(unsigned long long a, unsigned long long b)
=======
namespace
>>>>>>> parent of 10f28ac (fx)
=======
unsigned long long sum(unsigned long long a, unsigned long long b)
>>>>>>> parent of 34145dd (fx)
{
  if ( a > std::numeric_limits< unsigned long long >::max() - b)
  {
    throw std::overflow_error("overflow");
  }
  return a + b;
}
//}

sadofeva::list_lists_t sadofeva::transformList(const input_list_t & list)
{
  using iter_t = numbers_list_t::const_iterator;
  sadofeva::List< std::pair< iter_t,iter_t > > iter_list;
  for (auto && elem: list)
  {
    iter_list.push_back(std::make_pair(elem.second.begin(), elem.second.end()));
  }
  list_lists_t list_of_lists;
  bool is_end = false;
  do
  {
    numbers_list_t number_list;
    for (auto && iters: iter_list)
    {
      if (iters.first != iters.second)
      {
        number_list.push_back(*(iters.first));
        ++(iters.first);
      }
    }
    if (number_list.empty())
    {
      is_end = true;
    }
    else
    {
      list_of_lists.push_back(number_list);
    }
  }
  while (!is_end);
  return list_of_lists;
}

unsigned long sadofeva::sumNumbersFromList(const numbers_list_t & list)
{
  unsigned long sum = 0;
  for (auto && value: list)
  {
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    sum = sum1(sum,value);
=======
    sum = ::sum(sum,value);
>>>>>>> parent of 10f28ac (fx)
=======
    sum = sum(sum,value);
>>>>>>> parent of 34145dd (fx)
=======
    sum = sadofeva::sum(sum,value);
>>>>>>> parent of fa6257b (fx)
  }
  return sum;
}
