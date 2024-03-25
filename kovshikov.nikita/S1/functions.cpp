#include "functions.hpp"

void kovshikov::inputPairs(DoubleList<std::pair<std::string, DoubleList<size_t>>> &allPairs, bool &isBigNumber)
{
  int i = 0;
  while(!std::cin.eof())
  {
    i++;
    DoubleList<size_t> list;
    std::string listName;
    std::string integerString;
    std::cin >> listName;
    std::getline(std::cin, integerString);
    if(!listName.empty())
    {
      std::string tempString;
      size_t integer;
      for(size_t i = 0; i < integerString.length(); i++)
      {
        if(integerString[i] != ' ')
        {
          tempString.append(1, integerString[i]);
        }
        else
        {
          if(!tempString.empty())
          {
            integer = std::stoull(tempString);
            if(integer == std::numeric_limits<size_t>::max())
            {
              isBigNumber = true;
            }
            list.pushBack(integer);
            tempString.clear();
          }
        }
      }
      if(!tempString.empty())
      {
        integer = std::stoull(tempString);
        if(integer == std::numeric_limits<size_t>::max())
        {
          isBigNumber = true;
        }
        list.pushBack(integer);
      }
      allPairs.pushBack(std::pair<std::string, DoubleList<size_t>> {listName, list});
    }
  }
}

void kovshikov::outputListName(const DoubleList<std::pair<std::string, DoubleList<size_t>>> &allPairs)
{
  DoubleList<std::pair<std::string, DoubleList<size_t>>>::Iterator iterator = allPairs.begin();
  while(iterator != nullptr)
  {
    std::cout << iterator->first;
    iterator++;
    if(iterator != nullptr)
    {
      std::cout << " ";
    }
    else
    {
      std::cout << "\n";
    }
  }
}

void kovshikov::outputResult(const DoubleList<std::pair<std::string, DoubleList<size_t>>> &allPairs, const  bool &isBigNumber)
{
  DoubleList<size_t> summaList;
  DoubleList<DoubleList<size_t>> resultList;
  DoubleList<std::pair<std::string, DoubleList<size_t>>>::Iterator iteratorAllPairs = allPairs.begin();
  bool flag = true;
  while(flag == true)
  {
    size_t summa = 0;
    DoubleList<size_t> list;
    while(iteratorAllPairs != allPairs.end())
    {
      if(!iteratorAllPairs->second.empty())
      {
        summa += iteratorAllPairs->second.front();
        list.pushBack(iteratorAllPairs->second.front());
        iteratorAllPairs->second.popFront();
      }
      iteratorAllPairs++;
    }
    if(!list.empty())
    {
      summaList.pushBack(summa);
      resultList.pushBack(list);
      iteratorAllPairs = allPairs.begin();
    }
    else
    {
      flag = false;
    }
  }
  while(!resultList.empty())
  {
    DoubleList<size_t> list = resultList.front();
    while(!list.empty())
    {
      std::cout << list.front();
      list.popFront();
      if(!list.empty())
      {
        std::cout << " ";
      }
    }
    resultList.popFront();
    std::cout << "\n";
  }
  if(isBigNumber == false)
  {
    if(summaList.empty())
    {
      std::cout << 0 << "\n";
    }
    while(!summaList.empty())
    {
      std::cout << summaList.front();
      summaList.popFront();
      if(!summaList.empty())
      {
        std::cout << " ";
      }
      else
      {
        std::cout << "\n";
      }
    }
  }
}
