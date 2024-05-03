#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
  using OutList = popov::List<std::pair<std::string, popov::List<unsigned long long>>>;
  OutList OList;
  size_t sizeAll = 0;
  size_t sizeIn = 0;
  std::string input = "";
  while ((!std::cin.eof()) and (std::cin >> input))
  {
    if (isdigit(input[0]))
    {
      OList.tail->data.second.pushBack(std::stoull(input));
    }
    else
    {
      OList.pushBack(std::pair<std::string,popov::List<unsigned long long>> (input, popov::List<unsigned long long>()));
    }
  }
  if (OList.head == nullptr)
  {
    std::cout << 0 << "\n";
    return 0;
  }
  while (OList.iter.node != nullptr)
  {
    std::cout << OList.iter.node->data.first;
    OList.iter++;
    if (OList.iter.node != nullptr)
    {
    std::cout << " ";
    }
  }
  std::cout << "\n";
  OList.iterBegin();
  for (size_t i = 0; i != OList.size; i++)
  {
    size_t maxSizeIn = 0;
    while (OList.iter.node != nullptr)
    {
      maxSizeIn = OList.iter.node->data.second.size;
      if (maxSizeIn > sizeIn)
      {
        sizeIn = maxSizeIn;
      }
      OList.iter++;
    }
  }
  OList.iterBegin();
  sizeAll = OList.size * sizeIn;
  unsigned long long* sum = new unsigned long long[OList.size]{0};
  int count = 0;
  int flag = 0;
  for (size_t i = 0; i != sizeAll; i++)
  {
    if ((OList.iter.node != nullptr) and (i != 0))
    {
      OList.iter++;
    }
    if (OList.iter.node == nullptr)
    {
      OList.iterBegin();
      count++;
      std::cout << "\n";
      flag = 1;
    }
    if (OList.iter.node->data.second.iter.node != nullptr)
    {
      sum[count] += OList.iter.node->data.second.iter.node->data;
      if ((i != 0) and (flag != 1))
      {
        std::cout << " ";
      }
      if (flag == 1)
      {
        flag = 0;
      }
      std::cout << OList.iter.node->data.second.iter.node->data;
      OList.iter.node->data.second.iter++;
    }
  }
  if (sizeAll != 0)
  {
    std::cout << "\n";
  }
  for (int j = 0; j != count + 1; j++)
  {
    std::cout << sum[j];
    if (j != count)
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  delete[] sum;
  return 0;
}
