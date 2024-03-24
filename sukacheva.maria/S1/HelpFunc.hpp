#ifndef HELPFUNC_HPP
#define HELPFUNC_HPP

#include <iostream>
#include "List.hpp"

namespace sukacheva {

  List< std::pair< std::string, List< size_t > > > listInput(std::istream& in);
  size_t maxListSize(List< std::pair< std::string, List< size_t > > >& newList);
  void printNameList(List< std::pair< std::string, List< size_t > > >& newList);
  void printArgs(List< std::pair< std::string, List< size_t > > >& newList);
}

#endif
