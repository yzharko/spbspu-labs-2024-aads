#include "utils.hpp"

std::ostream& proselkov::outWrongParams(std::ostream& out)
{
  out << "Error: Wrong input parameters!\n";
  return out;
}

std::ostream& proselkov::outWrongSize(std::ostream& out)
{
  out << "Error: Wrong size! It must be positive!\n";
  return out;
}
