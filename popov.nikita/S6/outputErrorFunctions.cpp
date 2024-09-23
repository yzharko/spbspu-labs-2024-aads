#include "outputErrorFunctions.hpp"
#include <iostream>

std::ostream & popov::printInvalidParameters(std::ostream & out)
{
  out << "wrong number of parameters\n";
  return out;
}

std::ostream & popov::pringWrongSize(std::ostream & out)
{
  out << "wrong size parameter\n";
  return out;
}
