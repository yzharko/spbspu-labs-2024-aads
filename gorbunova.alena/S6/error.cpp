#include "error.hpp"
#include <iostream>

std::ostream& gorbunova::displayParameterError(std::ostream& out)
{
  out << "Invalid number of parameters provided.\n";
  return out;
}

std::ostream& gorbunova::displaySizeError(std::ostream& out)
{
  out << "The size parameter is invalid.\n";
  return out;
}
