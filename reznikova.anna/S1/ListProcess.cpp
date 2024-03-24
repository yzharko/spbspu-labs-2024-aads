#include "ListProcess.hpp"
#include <iostream>
#include <string>
#include <cstddef>
#include <limits>

void reznikova::inputList(std::istream & input, List< std::pair< std::string, List< size_t > > > & list, bool & overflow)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    list.pushBack({ line, List< size_t >() });
    while (input >> line && !std::isalpha(line[0]))
    {
      try
      {
        size_t num = stoull(line);
        list.getBack().second.pushBack(num);
      }
      catch (const std::exception& e)
      {
        overflow = 1;
      }
    }
  }
}

void reznikova::namesOutput(std::ostream & output, List< std::pair< std::string, List< size_t > > > & list)
{
  List< std::pair< std::string, List< size_t > > >::Iterator iterator = list.begin();
  while (iterator.getNode())
  {
//    if (iterator.getNode() != list.head_)
//    {
//      output << " ";
//    }
    output << iterator.getNode()->data_.first;
    if (iterator.getNode()->next_)
    {
      output << " ";
    }
    iterator++;
  }
  if (!list.empty())
  {
    output << "\n";
  }
}

size_t reznikova::findMaxLenOfArgs(List< std::pair < std::string, List< size_t > > > & list)
{
  List< std::pair< std::string, List< size_t > > >::Iterator iterator = list.begin();
  size_t max_size = 0;
  while (iterator.getNode())
  {
    size_t size = iterator.getNode()->data_.second.getSize();
    max_size = (max_size > size ? max_size : size);
    iterator++;
  }
  return max_size;
}

void reznikova::outputArgs(std::ostream & output, List< std::pair< std::string, List< size_t > > > & list, bool & overflow)
{
  List< size_t > sums;
  size_t max_size = findMaxLenOfArgs(list);
  const size_t maximum = std::numeric_limits< size_t >::max();
  for (size_t i = 0; i != max_size; i++)
  {
    size_t sum = 0;
    List< std::pair< std::string, List< size_t > > >::Iterator iterator = list.begin();
    while (iterator.getNode())
    {
      List< size_t >::Iterator args_iterator = iterator.getNode()->data_.second.begin();
      if (iterator.getNode()->data_.second.getSize() > i)
      {
        args_iterator = args_iterator.moveForward(i);
        if (sum > 0)
        {
          output << " ";
        }
        output <<  args_iterator.getNode()->data_;
        if (maximum - sum <= args_iterator.getNode()->data_)
        {
          overflow = 1;
          output << " ";
        }
        else
        {
          sum += args_iterator.getNode()->data_;
        }
      }
      iterator++;
    }
    sums.pushBack(sum);
    output << "\n";
  }
  if (overflow == 1)
  {
    throw std::logic_error("overflow");
  }
  List< size_t >::Iterator sum_iterator = sums.begin();
  while (sum_iterator.getNode())
  {
//    if (sum_iterator.getNode() != sums.head_)
//    {
//      output << " ";
//    }
    output << sum_iterator.getNode()->data_;
    if (sum_iterator.getNode()->next_)
    {
      output << " ";
    }
    sum_iterator++;
  }
  if (sums.empty())
  {
    output << 0;
  }
  output << "\n";
}
