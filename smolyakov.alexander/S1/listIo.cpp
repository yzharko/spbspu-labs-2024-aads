#include "listIo.hpp"
#include <cctype>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include "list.hpp"

using listOfPairs = smolyakov::List<std::pair<std::string, smolyakov::List<size_t>>>;

listOfPairs smolyakov::inputList(std::istream& inputStream)
{
  std::string rawInput = "";
  size_t inputNumber = 0;
  listOfPairs list;

  while (inputStream >> rawInput)
  {
    if (std::isalpha(rawInput[0]))
    {
      list.pushBack({rawInput, List<size_t>()});
    }
    else
    {
      try
      {
        inputNumber = std::stoull(rawInput);
      }
      catch (std::out_of_range& e)
      {
        throw std::overflow_error("Could not read list: value too big");
      }
      list.end()->second.pushBack(inputNumber);
    }
  }
  return list;
}

void smolyakov::outputPairListNames(std::ostream& outputStream, listOfPairs list)
{
  if (list.isEmpty())
  {
    return;
  }

  listOfPairs::Iterator iterator = list.begin();
  bool firstOutput = true;

  for (size_t i = 0; i < list.getSize(); i++)
  {
    if (firstOutput)
    {
      firstOutput = false;
    }
    else
    {
      outputStream << ' ';
    }

    outputStream << iterator->first;
    iterator++;
  }
  outputStream << '\n';
}

size_t getMaxSize(listOfPairs listOfPairs)
{
  listOfPairs::Iterator iterator = listOfPairs.begin();
  size_t maxSize = 0;
  size_t size = 0;

  while (iterator != listOfPairs.end())
  {
    size = iterator->second.getSize();
    maxSize = size > maxSize ? size : maxSize;
    iterator++;
  }
  return maxSize;
}

void smolyakov::rearrangeValues(listOfPairs& listOfPairs, smolyakov::List<smolyakov::List<size_t>>& lists)
{
  listOfPairs::Iterator iterator = listOfPairs.begin();

  size_t maxSize = getMaxSize(listOfPairs);
  for (size_t column = 0; column < maxSize; column++)
  {
    iterator = listOfPairs.begin();
    smolyakov::List<size_t> currentList = smolyakov::List<size_t>();

    while (iterator != ++listOfPairs.end())
    {
      bool canAppendNumber = column < iterator->second.getSize();
      if (canAppendNumber)
      {
        currentList.pushBack(iterator->second[column]);
      }
      iterator++;
    }
    lists.pushBack(currentList);
  }
}

void smolyakov::outputRearrangedLists(std::ostream& outputStream, smolyakov::List<smolyakov::List<size_t>>& lists)
{
  smolyakov::List<smolyakov::List<size_t>>::Iterator iterator = lists.begin();
  while (iterator != ++lists.end())
  {
    outputListValues(outputStream, *iterator);
    iterator++;
  }
}

void smolyakov::calculateSums(smolyakov::List<smolyakov::List<size_t>>& lists, smolyakov::List<size_t>& destination)
{
  smolyakov::List<smolyakov::List<size_t>>::Iterator iterator = lists.begin();
  const size_t maxPossibleValue = std::numeric_limits<size_t>::max();

  while (iterator != ++lists.end())
  {
    size_t sum = 0;
    smolyakov::List<size_t>::Iterator innerIterator = iterator->begin();
    while (innerIterator != ++(iterator->end()))
    {
      if (maxPossibleValue - sum < *innerIterator)
      {
        throw std::overflow_error("Could not calculate sum: value too big");
      }
      sum += *innerIterator;
      innerIterator++;
    }
    destination.pushBack(sum);
    iterator++;
  }
}


void smolyakov::outputListValues(std::ostream& outputStream, smolyakov::List<size_t>& list)
{
  if (!list.isEmpty())
  {
    smolyakov::List<size_t>::Iterator iterator = list.begin();
    bool firstOutput = true;
    while (iterator != ++list.end())
    {
      if (firstOutput)
      {
        firstOutput = false;
      }
      else
      {
        outputStream << ' ';
      }
      outputStream << *iterator;
      iterator++;
    }
    outputStream << '\n';
  }
}
