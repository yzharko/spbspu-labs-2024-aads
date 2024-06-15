#ifndef IOLISTS_HPP
#define IOLISTS_HPP
#include <iosfwd>
<<<<<<< HEAD
#include <string>
#include "list.hpp"

namespace sadofeva
{
  using numbers_list_t = List< unsigned long >;
  using input_list_t = List< std::pair< std::string,numbers_list_t > >;
  using list_lists_t = List< numbers_list_t >;
=======
#include "listfwd.hpp"

namespace sadofeva
{
>>>>>>> parent of 10f28ac (fx)
  input_list_t inputValues(std::istream & in);
  void printNames(const input_list_t & list , std::ostream & out);
  void printNumberList(const numbers_list_t & list , std::ostream & out);
}

#endif
