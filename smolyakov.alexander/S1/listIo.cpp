#include "listIo.hpp"
#include <cctype>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include "list.hpp"

using listOfPairs = smolyakov::List<std::pair<std::string, smolyakov::List<long long>>>;

listOfPairs smolyakov::inputList(std::istream& inputStream)
{
  std::string rawInput = "";
  long long inputNumber = 0;
  listOfPairs list;

  while (inputStream >> rawInput)
  {
    if (std::isalpha(rawInput[0]))
    {
      list.pushBack({rawInput, List<long long>()});
    }
    else
    {
      inputNumber = std::stoll(rawInput);
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

void smolyakov::rearrangeValues(listOfPairs& listOfPairs, smolyakov::List<smolyakov::List<long long>>& lists)
{
  listOfPairs::Iterator iterator = listOfPairs.begin();

  size_t maxSize = getMaxSize(listOfPairs);
  for (size_t column = 0; column < maxSize; column++)
  {
    iterator = listOfPairs.begin();
    smolyakov::List<long long> currentList = smolyakov::List<long long>();

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

void smolyakov::outputRearrangedLists(std::ostream& outputStream, smolyakov::List<smolyakov::List<long long>>& lists)
{
  smolyakov::List<smolyakov::List<long long>>::Iterator iterator = lists.begin();
  while (iterator != ++lists.end())
  {
    smolyakov::List<long long>::Iterator innerIterator = iterator->begin();
    bool firstOutput = true;
    while (innerIterator != ++iterator->end())
    {
      if (firstOutput)
      {
        firstOutput = false;
      }
      else
      {
        outputStream << ' ';
      }
      outputStream << *innerIterator;
      innerIterator++;
    }
    outputStream << '\n';
    iterator++;
  }
}

void smolyakov::calculateSums(smolyakov::List<smolyakov::List<long long>>& lists, smolyakov::List<long long>& destination)
{
  smolyakov::List<smolyakov::List<long long>>::Iterator iterator = lists.begin();
  const long long maxPossibleValue = std::numeric_limits<long long>::max();

  while (iterator != ++lists.end())
  {
    long long sum = 0;
    smolyakov::List<long long>::Iterator innerIterator = iterator->begin();
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


void smolyakov::outputListValues(std::ostream& outputStream, smolyakov::List<long long>& list)
{
  if (!list.isEmpty())
  {
    smolyakov::List<long long>::Iterator iterator = list.begin();
    while (iterator != ++list.end())
    {
      outputStream << *iterator << ' ';
      iterator++;
    }
    outputStream << '\n';
  }
}
