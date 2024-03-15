#include "SequenceHandler.h"
#include <iostream>
#include <limits>

void SequenceHandler::addSequence(const std::string& name, const List<unsigned long long>& sequence)
{
  names.push_back(name);
  sequences.push_back(sequence);
}

void SequenceHandler::printSequences()
{
  for (auto it = names.begin(); it != names.end(); ++it)
  {
    std::cout << *it << (it + 1 == names.end() ? "" : " ");
  }
  if (*names.begin() != "")
  {
    std::cout << "\n";
  }
}

void SequenceHandler::rearrangeAndPrint()
{
  size_t maxLen = 0;
  auto seqIt = sequences.head;
  while (seqIt != nullptr)
  {
    maxLen = std::max(maxLen, seqIt->data.size());
    seqIt = seqIt->next;
  }

  unsigned long long* sums = new unsigned long long[maxLen]{};

  int s = 0;
  for (size_t i = 0; i < maxLen; ++i)
  {
    seqIt = sequences.head;
    while (seqIt != nullptr)
    {
      List<unsigned long long>& currentSeq = seqIt->data;
      auto numIt = currentSeq.head;
      size_t count = 0;

      while (count < i && numIt != nullptr)
      {
        numIt = numIt->next;
        count++;
      }
      if (numIt != nullptr)
      {
        std::cout << (s ? " " : "");
        s = 1;
        std::cout << numIt->data;
        if (sums[i] > std::numeric_limits<unsigned long long>::max() - numIt->data)
        {
          std::cout << "\n";
          delete[] sums;
          throw std::overflow_error("Sum of numbers is too big.");
        }
        sums[i] += numIt->data;
      }

      seqIt = seqIt->next;
    }
    std::cout << "\n";
    s = 0;
  }

  if (!maxLen)
  {
    std::cout << "0\n";
  }

  for (size_t i = 0; i < maxLen; ++i)
  {
    std::cout << sums[i] << (i == (maxLen - 1) ? "\n" : " ");
  }

  delete[] sums;
}
