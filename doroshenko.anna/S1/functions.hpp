#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "list.hpp"
#include <string>
#include <iostream>

namespace doroshenko
{
  List< std::pair< std::string, List< size_t > > > listInput(std::istream& input);
  size_t getMaxSize(List< std::pair< std::string, List< size_t > > >& list);
  void listOutput(List< std::pair< std::string, List< size_t > > >, std::ostream& output);
}

#endif
