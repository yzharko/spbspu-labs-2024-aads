#include "outputFunctions.hpp"
#include <iostream>

std::ostream& lisitsyna::printInvalidParameters(std::ostream& out)
{
  out << "wrong number of parameters\n";
  return out;
}

std::ostream& lisitsyna::pringWrongSize(std::ostream& out)
{
  out << "wrong size parameter\n";
  return out;
}
