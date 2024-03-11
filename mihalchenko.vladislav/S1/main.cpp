#include <iostream>
#include <string>
#include "list.hpp"
#include <utility>
#include <cstdio>
#include <limits>

using namespace mihalchenko;

int main()
{
  using mainList = mihalchenko::List<std::pair<std::string, mihalchenko::List<size_t>>>;
  mainList mixedList;
  using integerList = mihalchenko::List<size_t>;
  integerList tempIntList;

  std::string inputStr;
  std::string slovo;

  bool overflow = false;

  size_t ullMax = std::numeric_limits<size_t>::max();

  size_t maxLenOfSecondList = 0;
  size_t CountSecondList = 0;
  size_t CountmixedList = 0;

  while (std::cin >> inputStr)
  {
    if (!isdigit(inputStr[0]))
    {
      slovo = inputStr;
      tempIntList.clear();
      CountSecondList = 0;

      mixedList.push_back(std::make_pair(slovo, tempIntList));
      CountmixedList++;

      if (std::cin.peek() == '\n')
      {
        continue;
      }
    }
    else
    {
      size_t wrem = 0;
      sscanf(inputStr.c_str(), "%zu", &wrem);
      mixedList[CountmixedList - 1].second.push_back(wrem);
      if (inputStr == std::to_string(wrem))
      {
        CountSecondList++;
        if (std::cin.peek() == '\n')
        {
          if (maxLenOfSecondList < CountSecondList)
          {
            maxLenOfSecondList = CountSecondList;
          }
          continue;
        }
      }
      else
      {
        std::cerr << "Input overflow!";
        return 1;
      }
    }
  }

  if (mixedList.size_ == 0)
  {
    std::cout << 0 << std::endl;
    return 0;
  }

  for (size_t ind = 0; ind < mixedList.size_; ind++)
  {
    std::cout << mixedList[ind].first;
    if (ind != mixedList.size_ - 1)
    {
      std::cout << " ";
    }
  }
  // std::cout << "!";

  if (maxLenOfSecondList == 0)
  {
    std::cout << std::endl;
    std::cout << 0 << std::endl;
    return 0;
  }
  std::cout << std::endl;

  size_t summa = 0;
  bool flgNewStr = false;
  for (size_t numericView = 0; numericView < maxLenOfSecondList; numericView++)
  {
    flgNewStr = true;
    summa = 0;
    for (size_t i = 0; i < mixedList.size_; i++)
    {
      if (mixedList[i].second.size_ > numericView)
      {
        if (flgNewStr)
        {
          std::cout << mixedList[i].second[numericView];
          flgNewStr = false;
        }
        else
        {
          std::cout << " " << mixedList[i].second[numericView];
        }
        if (ullMax - mixedList[i].second[numericView] >= summa)
        {
          summa = summa + mixedList[i].second[numericView];
        }
        else
        {
          overflow = true;
        }
      }
    }
    // std::cout << "!";
    std::cout << std::endl;
    tempIntList.push_back(summa);
  }
  if (overflow)
  {
    std::cerr << "Input overflow!";
    return 1;
  }
  for (size_t i = 0; i < tempIntList.size_; i++)
  {
    std::cout << tempIntList[i];
    if (i != tempIntList.size_ - 1)
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  // std::cout << "!";
  return 0;
}
