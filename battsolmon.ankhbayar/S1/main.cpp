#include "list.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <stdexcept>

namespace
{
  unsigned long long sum(unsigned long long a, unsigned long long b)
  {
    if (a > std::numeric_limits< unsigned long long >::max() - b)
    {
      throw std::overflow_error("Overflow!");
    }
    return a + b;
  }
}
int main()
{
  std::string line;
  std::vector< std::pair< std::string, List< unsigned long long > > > sequences;
  size_t maxLen = 0;
  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    List< unsigned long long > list;
    unsigned long long num;
    size_t count = 0;
    while (!iss.fail() && !iss.eof())
    {
      iss >> num;
      if (iss.fail())
      {
        std::cerr << "Input error\n";
        return 1;
      }
      list.push_back(num);
      ++count;
    }
    maxLen = std::max(maxLen, count);
    sequences.emplace_back(name, std::move(list));
  }
  bool first = true;
  for (const auto & seq: sequences)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      std::cout << ' ';
    }
    std::cout << seq.first;
  }
  if (sequences.empty())
  {
    std::cout << 0 << '\n';
    return 0;
  }
  std::cout << '\n';
  for (size_t i = 0; i < maxLen; ++i)
  {
    first = true;
    for (const auto & seq: sequences)
    {
      const auto & list = seq.second;
      auto it = list.begin();
      for (size_t j = 0; j < i && it != list.end(); ++j)
      {
        ++it;
      }
      if (it != list.end())
      {
        if (first)
        {
          first = false;
        }
        else
        {
          std::cout << ' ';
        }
        std::cout << *it;
      }
    }
    std::cout << '\n';
    if (sequences.empty())
    {
      std::cout << 0;
    }
  }
  std::vector< unsigned long long > sums(maxLen, 0);
  try
  {
    for (size_t i = 0; i < maxLen; ++i)
    {
      for (const auto & seq: sequences)
      {
        const auto & list = seq.second;
        auto it = list.begin();
        for (size_t j = 0; j < i && it != list.end(); ++j)
        {
          ++it;
        }
        if (it != list.end())
        {
          sums[i] = sum(sums[i], *it);
        }
      }
    }
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  first = true;
  bool foundNonZero = false;
  for (auto sum: sums)
  {
    if (sum != 0)
    {
      foundNonZero = true;
    }
    if (foundNonZero)
    {
      if (first)
      {
        first = false;
      }
      else
      {
        std::cout << ' ';
      }
      std::cout << sum;
    }
  }
  if (sums.empty())
  {
    std::cout << '0';
  }
  std::cout << '\n';
  return 0;
}
