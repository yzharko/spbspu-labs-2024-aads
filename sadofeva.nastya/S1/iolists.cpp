#include <iostream>
#include "iolists.hpp"
#include "split.hpp"

sadofeva::input_list_t sadofeva::inputValues(std::istream & in)
{
  sadofeva::input_list_t input_list;
  do
  {
    std::string name, value;
    in >> name;
    std::getline(in,value);
    input_list.push_back(std::make_pair(name,sadofeva::splitNumbers(value)));
  }
  while (!in.eof());
  return input_list;
}

void sadofeva::printNames(const input_list_t & list, std::ostream & out)
{
  bool first = true;
  for (auto && elem: list)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      out << ' ';
    }
    out << elem.first;
  }
}

void sadofeva::printNumberList(const numbers_list_t & list, std::ostream & out)
{
  bool first = true;
  for (auto && value: list)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      out << ' ';
    }
    out << value;
  }
}
