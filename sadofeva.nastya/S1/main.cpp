#include <iostream>
#include <string>
#include "task.hpp"
#include "iolists.hpp"

int main()
{
  sadofeva::input_list_t input_list = sadofeva::inputValues(std::cin);
  if (input_list.empty())
  {
    std::cout << "0";
    return 0;
  }
  sadofeva::printNumes(input_list,std::cout);
  std:: cout << "\n";
  sadofeva::list_lists_t list_of_lists = sadofeva::transfromList(input_list);
  for (auto && nlist: list_of_lists)
  {
    sadofeva::printNumberList(nlist,std::cout);
    std::cout << "\n";
  }
  bool first = true;
  for (auto && nlist: list_of_lists)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      std::cout << " ";
    }
    std::cout << sadofeva::sumNumbersFromList(nlist);
  }
  if (first)
  {
    std::cerr << There is no sum of lists\n";
    return 1;
  }
  std::cout << "\n";
  return 0;
}
