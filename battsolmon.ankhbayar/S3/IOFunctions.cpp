#include "IOFunctions.hpp"
#include <iostream>
#include "cutFunctions.hpp"

void ankh::inputFromFile(std::istream & in, BSTree< std::string, BSTree< int, std::string, int >, int > & data)
{
  std::string dataLine = "";
  std::string name = "";
  std::string value = "";
  int key = 0;
  using data_t = ankh::BSTree< int, std::string, int >;

  while (std::getline(in, dataLine))
  {
    data_t dataSet;
    name = ankh::getName(dataLine);
    while (!dataLine.empty())
    {
      key = int(ankh::getNumber(dataLine));
      value = ankh::getName(dataLine);
      dataSet.insert(std::make_pair(key, value));
    }
    data.insert(std::make_pair(name, dataSet));
  }
}

std::ostream & ankh::printInvalidCommandMessage(std::ostream & out)
{
  out << "<INVALID COMMAND>" << "\n";
  return out;
}

std::ostream & ankh::printEmptyDataset(std::ostream & out)
{
  out << "<EMPTY>" << "\n";
  return out;
}
