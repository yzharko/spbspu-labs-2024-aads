#include <iostream>
#include "list.hpp"

int main()
{
  using OutList = popov::List<std::pair<std::string,popov::List<int>>>;
  OutList OList;
  size_t sizeAll = 0;
  size_t sizeIn = 0;
  std::string input = "";
  while (!std::cin.eof())
  {
    std::cin >> input;
    if (isdigit(input[0]))
    {
      OList.tail->data.second.pushBack(std::stoi(input));
    }
    else
    {
      OList.pushBack(std::pair<std::string,popov::List<int>> (input, popov::List<int>()));
    }
  }
  if (OList.head == nullptr)
  {
    std::cout << 0 << "\n";
  }
  while (OList.iter.node->next != nullptr)
  {
    std::cout << OList.iter.node->data.first << " ";
    OList.iter++;
  }
  std::cout << "\n";
  OList.iterBegin();
  for (size_t i = 0; i != OList.size; i++)
  {
    while (OList.iter.node->next != nullptr)
    {
      sizeIn += OList.iter.node->data.second.size;
      OList.iter++;
    }
  }
  sizeAll = OList.size * sizeIn;
  int sum[OList.size];
  int count = 0;
  for (size_t i = 0; i != sizeAll; i++)
  {
    if (OList.iter.node->data.second.iter.node->next != nullptr)
    {
      sum[count] += OList.iter.node->data.second.iter.node->data;
      std::cout << OList.iter.node->data.second.iter.node->data << " ";
      OList.iter.node->data.second.iter++;
    }
    if (OList.iter.node->next == nullptr)
    {
      OList.iterBegin();
      count++;
      std::cout << "\n";
    }
    else
    {
      OList.iter++;
    }
  }
  for (int j = 0; j != count + 1; j++)
  {
    std::cout << sum[j] << " ";
  }
  std::cout << "\n";
  return 0;
}
