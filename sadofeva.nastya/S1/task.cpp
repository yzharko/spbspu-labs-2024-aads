#include "task.hpp"

sadofeva::list_lists_t sadofeva::transformList(const input_list_t & list)
{
  using iter_t = numbers_list_t::const_iterator;
  sadofeva::List<std::pair<iter_t,iter_t>> iter_list;
  for (auto && elem:: list)
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
  reutrn list_of_lists;
}
