#ifndef IOLISTS_HPP
#define IOLISTS_HPP
#include <iosfwd>
#include "listfwd.hpp"

namespace sadofeva
{
  input_list_t inputValues(std::istream & in);
  void printNames(const input_list_t & list , std::ostream & out);
  void printNumberList(const numbers_list_t & list , std::ofstream & out, char delimeter = ' ');
}

#endif
