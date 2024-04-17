#include "ListProcess.hpp"
#include <iostream>
#include <string>
#include <cstddef>
#include <limits>
#include "Iterator.hpp"
#include "ConstIterator.hpp"

void reznikova::inputList(std::istream & input, List< std::pair< std::string, List< size_t > > > & list)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    list.pushBack({ line, List< size_t >() });
    while (input >> line && !std::isalpha(line[0]))
    {
      size_t num = stoull(line);
      list.getBack().second.pushBack(num);
    }
  }
}

size_t reznikova::findMaxLenOfArgs(List< std::pair < std::string, List< size_t > > > & list)
{
  reznikova::details::Iterator< std::pair< std::string, List< size_t > > > iterator = list.begin();
  size_t max_size = 0;
  while (iterator != list.end())
  {
    size_t size = iterator->second.getSize();
    max_size = (max_size > size ? max_size : size);
    iterator++;
  }
  return max_size;
}

reznikova::List< size_t > reznikova::countSums(List< std::pair< std::string, List< size_t > > > & list)
{
  bool overflow = false;
  List< size_t > sums;
  size_t max_size = findMaxLenOfArgs(list);
  const size_t maximum = std::numeric_limits< size_t >::max();
  for (size_t i = 0; i != max_size; i++)
  {
    size_t sum = 0;
    reznikova::details::Iterator< std::pair< std::string, List< size_t > > > iterator = list.begin();
    while (iterator != list.end())
    {
      reznikova::details::Iterator< size_t > args_iterator = iterator->second.begin();
      if (iterator->second.getSize() > i)
      {
        for (size_t j = 0; j < i; j++)
        {
          args_iterator++;
        }
        if (maximum - sum <= *args_iterator)
        {
          overflow = true;
        }
        else
        {
          sum += *args_iterator;
        }
      }
      iterator++;
    }
    sums.pushBack(sum);
  }
  if (overflow == true)
  {
    throw std::overflow_error("overflow");
  }
  return sums;
}

void reznikova::outputNames(std::ostream & output, List< std::pair< std::string, List< size_t > > > & list)
{
  reznikova::details::Iterator< std::pair< std::string, List< size_t > > > iterator = list.begin();
  while (iterator != list.end())
  {
    if (iterator != list.begin())
    {
      output << " ";
    }
    output << iterator->first;
    iterator++;
  }
  if (!list.empty())
  {
    output << "\n";
  }
}

void reznikova::outputArgs(std::ostream & output, List< std::pair< std::string, List< size_t > > > & list)
{
  size_t max_size = findMaxLenOfArgs(list);
  for (size_t i = 0; i != max_size; i++)
  {
    size_t sum = 0;
    reznikova::details::Iterator< std::pair< std::string, List< size_t > > > iterator = list.begin();
    while (iterator != list.end())
    {
      reznikova::details::Iterator< size_t > args_iterator = iterator->second.begin();
      if (iterator->second.getSize() > i)
      {
        for (size_t j = 0; j < i; j++)
        {
          args_iterator++;
        }
        if (iterator != list.begin())
        {
          output << " ";
        }
        output <<  *args_iterator;
      }
      iterator++;
    }
    output << "\n";
  }
}

void reznikova::outputSums(std::ostream & output, List< size_t > & sums)
{
  reznikova::details::Iterator< size_t > sum_iterator = sums.begin();
  while (sum_iterator != sums.end())
  {
    if (sum_iterator != sums.begin())
    {
      output << " ";
    }
    output << *sum_iterator;
    sum_iterator++;
  }
  if (sums.empty())
  {
    output << 0;
  }
  output << "\n";
}
