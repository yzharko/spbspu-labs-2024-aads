#include <iostream>
#include <string>
#include "task.hpp"
#include "iolists.hpp"

int main()
{
  sadofeva::input_list_t input_list = sadofeva::inputValues(std::cin);
  if (input_list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  sadofeva::printNames(input_list,std::cout);
  std:: cout << "\n";
  sadofeva::list_lists_t list_of_lists = sadofeva::transformList(input_list);
  for (auto && nlist: list_of_lists)
  {
    sadofeva::printNumberList(nlist, std::cout);
    std::cout << "\n";
  }
  sadofeva::numbers_list_t sums{};
  try
  {
    for (auto && nlist: list_of_lists)
    {
      sums.push_back(sadofeva::sumNumbersFromList(nlist));
    }
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  bool first = true;
  for (auto && sum: sums)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      std::cout << " ";
    }
    std::cout << sum;
  }
  if (first)
  {
    std::cout << 0;
  }
  std::cout << "\n";
  return 0;
}
