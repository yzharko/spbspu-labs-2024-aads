#include "functions.hpp"
#include <limits>

doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > doroshenko::listInput(std::istream& input)
{
  std::string inputString = "";
  doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > inputList;
  unsigned long long readNumber = 0;
  const size_t maximum = std::numeric_limits< size_t >::max();
  while (input >> inputString)
  {
    if (std::isalpha(inputString[0]))
    {
      inputList.pushBack({ inputString, doroshenko::List< size_t >() });
    }
    else
    {
      readNumber = std::stoull(inputString);
      if (readNumber > maximum)
      {
        throw std::overflow_error("overflow error");
      }
      else
      {
        inputList.back().second.pushBack(readNumber);
      }
    }
  }
  return inputList;
}

void doroshenko::listOutput(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > > list, std::ostream& output)
{
  List< std::pair< std::string, doroshenko::List< size_t > > >::Iterator iterator = list.begin();
  size_t maxSize = getMaxSize(list);
  doroshenko::List< size_t >::Iterator localIterator = doroshenko::List< size_t >::ConstIterator();
  List< size_t > sums;
  List< size_t >::Iterator iteratorForSums;
  const size_t maximum = std::numeric_limits< size_t >::max();
  size_t sum = 0;
  bool overflowError = false;
  if (!list.isEmpty())
  {
    while (iterator != list.end())
    {
      if (iterator != list.begin())
      {
        output << " ";
      }
      output << iterator->first;
      iterator++;
    }
    output << "\n";
    for (size_t index = 0; index < maxSize; index++)
    {
      iterator = list.begin();
      while (iterator != list.end())
      {
        if (iterator->second[index] != nullptr)
        {
          if (sum > 0)
          {
            output << " ";
          }
          localIterator = List< size_t >::ConstIterator(iterator->second[index]);
          std::cout << *localIterator;
          if (maximum - sum < *localIterator)
          {
            overflowError = true;
            output << "\n";
            throw std::overflow_error("overflow error");
          }
          else
          {
            sum = sum + *localIterator;
          }
        }
        iterator++;
      }
      if (!overflowError)
      {
        sums.pushBack(sum);
      }
      sum = 0;
      overflowError = false;
      output << "\n";
    }

    iteratorForSums = sums.begin();
    if (sums.isEmpty())
    {
      output << 0;
    }
    else
    {
      while (iteratorForSums != sums.end())
      {
        if (iteratorForSums != List< size_t >::ConstIterator())
        {
          if (iteratorForSums != sums.begin())
          {
            output << " ";
          }
          output << *iteratorForSums;
        }
        iteratorForSums++;
      }
    }
    output << "\n";
  }
  else
  {
    output << 0 << "\n";
  }
}

size_t doroshenko::getMaxSize(doroshenko::List< std::pair< std::string, doroshenko::List< size_t > > >& list)
{
  size_t size = 0;
  size_t maxSize = 0;
  List< std::pair< std::string, doroshenko::List< size_t > > >::Iterator iterator = list.begin();
  while (iterator != List< std::pair< std::string, doroshenko::List< size_t > > >::ConstIterator())
  {
    size = iterator->second.getSize();
    maxSize = size > maxSize ? size : maxSize;
    iterator++;
  }
  return maxSize;
}
