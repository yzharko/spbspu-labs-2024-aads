#include <algorithm>
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
  size_t count = 0;
  size_t max_len = 0;
  size_t curr_len = 0;
  bool isSeq = false;
  while (std::cin)
  {
    std::cin >> input;
    if (!std::cin)
    {
      if (curr_len > max_len)
      {
        max_len = curr_len;
      }
      if (count == 0)
      {
        pairs[0].second.clear();
        std::cout << input << '\n';
        std::cout << 0 << '\n';
        return 0;
      }
      continue;
    }
    if (isdigit(input[0]))
    {
      isSeq = true;
      try
      {
        unsigned long long temp = std::stoull(input);
        pairs[count - 1].second.pushBack(temp);
      }
      catch(...)
      {
        std::cerr << "Invalid number\n";
        for (size_t i = 0; i < count; i++)
        {
          pairs[i].second.clear();
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
      }
      curr_len = 0;
      pairs[count] = std::pair< std::string, storage_t > (input, storage_t());
	  count++;
    }
  }
  if (isSeq == false)
  {
    std::cout << 0 << '\n';
    return 0;
  }
  unsigned long long sums[max_len] {};
  for (size_t i = 0; i < count; i++)
  {
    std::cout << pairs[i].first << ' ';
  }
  std::cout << pairs[count].first << '\n';
  for (size_t i = 0; i <= max_len - 1; i++)
  {
    storage_t list;
    for (size_t j = 0; j < count; j++)
    {
      unsigned long long temp = pairs[j].second.getValue(i);
      if (temp)
      {
        list.pushBack(temp);
      }
    }
    list.print();
    try
      {
        sums[i] = list.getSum();
      }
    catch(const std::overflow_error & e)
      {
        for (size_t j = 0; j < count; j++)
        {
          pairs[j].second.clear();
        }
        list.clear();
        std::cerr << "Overflow_error: " << e.what() << '\n';
        return 1;
      }
    list.clear();
  }
  for (size_t i = 0; i < max_len - 1; i++)
  {
    std::cout << sums[i] << ' ';
  }
  std::cout << sums[max_len - 1] << '\n';
  for (size_t j = 0; j < count; j++)
  {
    pairs[j].second.clear();
  }
  return 0;
}
