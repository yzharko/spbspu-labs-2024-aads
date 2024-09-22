#ifndef DICTS_HPP
#define DICTS_HPP
#include <string>
#include "tree.hpp"

namespace panov
{
  using word_t = std::pair< std::string, std::string >;
  using dict_t = List< word_t >;
  using dicts_t = Tree< std::string, dict_t >;
}
#endif
