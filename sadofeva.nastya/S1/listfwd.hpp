#ifndef LIST_FWD_HPP
#define LIST_FWD_HPP
#include <string>
#include "list.hpp"

namespace sadofeva
{
  using numbers_list_t = List<unsigned long>;
  using input_list_t = List<std::pair<std::string,numbers_list_t>>;
  using list_lists_t = List<numbers_list_t>;
}

#endif
