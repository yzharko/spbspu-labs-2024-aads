#include "ListProcess.hpp"
#include <iostream>
#include <string>

void reznikova::inputList(std::istream & input, reznikova::List< std::pair< std::string, List<int> > > & list)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    list.pushBack({ line, List< int >() });
    while (input >> line && !std::isalpha(line[0]))
    {
      list.back().second.pushBack(stoi(line));
    }
  }
}

void reznikova::namesOutput(std::ostream & output, List< std::pair< std::string, List< int > > > & list)
{
  ListIterator< std::pair< std::string, List< int > > > iterator = list.begin();
  while (iterator.node)
  {
    output << iterator.node->data_.first << " ";
    iterator++;
  }
}

size_t reznikova::findMaxLenOfArgs(List< std::pair < std::string, List< int > > > & list)
{
  ListIterator< std::pair< std::string, List< int > > > iterator = list.begin();
  size_t max_size = 0;
  while (iterator.node)
  {
    size_t size = iterator.node->data_.second.size_;
    max_size = (max_size > size ? max_size : size);
    iterator++;
  }
  return max_size;
}
