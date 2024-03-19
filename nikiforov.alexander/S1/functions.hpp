#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

namespace nikiforov
{
  template <typename T>
  void input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair);

  template <typename T>
  void outputName_(List< std::pair< std::string, List< T > > >& seqsPair, size_t& maxSize);

  template <typename T>
  void outputSeqs_(List< std::pair< std::string, List< T > > >& seqsPair, List<T>& listSumm, size_t maxSize);

  template <typename T>
  void outputSumm_(List<T>& listSumm, size_t maxSize);

  size_t max(const size_t first_param, const size_t second_param);
}

template<typename T>
void nikiforov::input_(std::istream& input, List< std::pair< std::string, List< T > > >& seqsPair)
{
  Iterator< std::pair< std::string, List< unsigned long long > > > iterSeqsPair = seqsPair.begin();
  std::string elemSeq;
  bool firstLine = false;

  while (input >> elemSeq)
  {
    if (isdigit(elemSeq[0]))
    {
      (*iterSeqsPair).second.push_back(std::stoull(elemSeq));
    }
    else
    {
      seqsPair.push_back({ elemSeq,{} });
      if (!firstLine)
      {
        iterSeqsPair = seqsPair.begin();
        firstLine = true;
      }
      else
      {
        iterSeqsPair++;
      }
    }
  }
}

template<typename T>
void nikiforov::outputName_(List<std::pair<std::string, List<T>>>& seqsPair, size_t& maxSize)
{
  Iterator< std::pair< std::string, List< unsigned long long > > > iterSeqsPair = seqsPair.begin();
  size_t countNames = seqsPair.size();

  for (iterSeqsPair = seqsPair.begin(); iterSeqsPair != seqsPair.end(); ++iterSeqsPair)
  {
    if (countNames == 1)
    {
      std::cout << iterSeqsPair->first << "\n";
    }
    else
    {
      std::cout << iterSeqsPair->first << " ";
    }
    maxSize = max(maxSize, iterSeqsPair->second.size());
    countNames--;
  }
}

template<typename T>
void nikiforov::outputSeqs_(List<std::pair<std::string, List<T>>>& seqsPair, List<T>& listSumm, size_t maxSize)
{
  if (maxSize != 0)
  {
    Iterator< std::pair< std::string, List< unsigned long long > > > iterSeqsPair = seqsPair.begin();
    Iterator< unsigned long long > iterList = (*iterSeqsPair).second.begin();
    size_t countInSeq = 0;
    unsigned long long summ = 0;
    bool firstElem = false;
    bool overflow = false;

    while (countInSeq < maxSize)
    {
      firstElem = false;
      for (iterSeqsPair = seqsPair.begin(); iterSeqsPair != seqsPair.end(); ++iterSeqsPair)
      {
        iterList = (*iterSeqsPair).second.begin();
        for (size_t i = 0; i < countInSeq; i++)
        {
          if (iterList != nullptr)
          {
            iterList++;
          }
        }
        if (iterList != nullptr)
        {
          firstElem ? std::cout << " " << *iterList : std::cout << *iterList;
          firstElem = true;
          if ((std::numeric_limits<unsigned long long>::max() - summ) > *iterList)
          {
            summ += *iterList;
          }
          else
          {
            overflow = true;
          }
        }
      }
      std::cout << "\n";
      countInSeq++;
      listSumm.push_back(summ);
      summ = 0;
    }
    if (overflow)
    {
      throw std::overflow_error("Error: overflow!");
    }
  }
}

template<typename T>
void nikiforov::outputSumm_(List<T>& listSumm, size_t maxSize)
{
  if (maxSize != 0)
  {
    Iterator< unsigned long long > iterListSummEnd = listSumm.end();
    size_t count = 0;
    for (Iterator< unsigned long long > iterListSumm = listSumm.begin(); iterListSumm != iterListSummEnd; ++iterListSumm)
    {
      count++;
      listSumm.size() == count ? std::cout << *iterListSumm : std::cout << *iterListSumm << " ";
    }
    std::cout << "\n";
  }
  else
  {
    std::cout << 0 << "\n";
  }
}

size_t nikiforov::max(const size_t first_param, const size_t second_param)
{
  return first_param > second_param ? first_param : second_param;
}

#endif
