#include "IOFunctions.hpp"

void malanin::readTree(std::istream& in, tree_t& container)
{
  long long tempKey = 0;
  std::string tempValue = "";
  while (!in.eof())
  {
    in >> tempKey >> tempValue;
    if (in.fail())
    {
      return;
    }
    container.insert(tempKey, tempValue);
  }
}

void malanin::sendEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}
