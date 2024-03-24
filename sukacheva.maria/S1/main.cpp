#include <iostream>
#include "List.hpp"
#include <string>
#include "HelpFunc.hpp"
#include <exception>

int main() {
  using namespace sukacheva;
  try {
    List< std::pair< std::string, List< size_t > > > newList = listInput(std::cin);
    if (maxListSize(newList) == 0) {
      if (!newList.empty())
      {
        printNameList(newList);
      }
      std::cout << "0\n";
    }
    else {
      printNameList(newList);
      printArgs(newList);
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
