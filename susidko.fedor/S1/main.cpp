#include <algorithm>
#include "Iterator.hpp"
#include "list.hpp"
#include "node.hpp"
#include <iostream>
#include <string>

int main() {
  const int len = 15;
  using storage_t = susidko::List < unsigned long long >;
  storage_t data;
  std::pair < std::string, storage_t > pairs[len];
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
      try
      {
        unsigned long long temp = std::stoull(input);
        pairs[count].second.pushBack(temp);
      }
      catch(...)
      {
        std::cerr << "Invalid number";
        for (size_t i = 0; i <= count; i++)
        {
          pairs[i].second.free();
        }
        return 1;
      }
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
      pairs[count] = std::pair< std::string, storage_t > (input, storage_t());
    }
  }
  if (isSeq == 0)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  int sums[max_len] {};
  for (size_t i = 0; i != count; i++)
  {
    std::cout << pairs[i].first << ' ';
  }
  std::cout << pairs[count].first << '\n';
  
  for (size_t i = 0; i < max_len; i++)
  {
    for (size_t j = 0; j <= count; j++)
    {
      sums[i] += pairs[j].second.getValue();
      pairs[j].second.printNext();
    }
    std::cout << '\n';
  }
  for (size_t i = 0; i != max_len - 1; i++)
  {
    std::cout << sums[i] << ' ';
  }
  std::cout << sums[max_len - 1] << '\n';
  for (size_t j = 0; j <= count; j++)
  {
    pairs[j].second.free();
  }
  return 0;
}
