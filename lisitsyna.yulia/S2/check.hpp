#ifndef CHECK_HPP
#define CHECK_HPP

#include <string>

namespace lisitsyna
{
  bool is_operator(const std::string & opr);
  int get_priority(const std::string & opr);
}

#endif
