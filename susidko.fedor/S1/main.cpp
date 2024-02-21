#include <algorithm>
#include "Iterator.hpp"
#include "list.hpp"
#include "node.hpp"
#include <iostream>
#include <string>

int main() {
  const int len = 15;
  using storage_t = susidko::List < int >;
  storage_t data;
  std::pair < std::string, susidko::List < int > > pairs[len];
  std::string input = "";
  size_t count = -1;
  size_t max_len = 0;
  size_t curr_len = 0;
  bool isSeq = 0;
  while (std::cin)
  {
    std::cin >> input;
    if (!std::cin)
    {
      if (curr_len > max_len)
      {
        max_len = curr_len;
      }
      continue;
    }
    if (isdigit(input[0]))
    {
      isSeq = 1;
      pairs[count].second.pushBack(std::stoi(input));
      curr_len ++;
    }
    else
    {
      if (curr_len > max_len)
      {
        max_len = curr_len;
        curr_len = 0;
      }
      count++;
      pairs[count] = std::pair< std::string, susidko::List < int > > (input, susidko::List < int >());
    }
  }
  if (isSeq == 0)
  {
    std::cout << 0;
    return 0;
  }
  int sums[max_len] {};
  for (size_t i = 0; i != count; i++)
  {
    std::cout << pairs[i].first << ' ';
  }
  std::cout << pairs[count].first << '\n';
  for (size_t i = 0; i != max_len; i++)
  {
    for (size_t j = 0; j != count; j++)
    {
      sums[i] += pairs[j].second.getValue();
      pairs[j].second.printNext(1);
    }
    sums[i] += pairs[count].second.getValue();
    pairs[count].second.printNext(0);
    std::cout << '\n';
  }
  for (size_t i = 0; i != max_len - 1; i++)
  {
    std::cout << sums[i] << ' ';
  }
  std::cout << sums[max_len - 1];
  /*for (size_t j = 0; j != count; j++)
    {
      pairs[j].second.free();
    }*/
  return 0;
}
