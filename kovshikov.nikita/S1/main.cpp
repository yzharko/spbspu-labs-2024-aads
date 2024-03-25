#include "doublelist.hpp"
#include "functions.hpp"

using namespace kovshikov;
int main()
{
  DoubleList<std::pair<std::string, DoubleList<size_t>>> allPairs;
  bool isBigNumber = false;
  inputPairs(allPairs, isBigNumber);
  outputListName(allPairs);
  outputResult(allPairs, isBigNumber);
  if(isBigNumber == true)
  {
    std::cerr << "too many numbers were entered\n";
    return 1;
  }
  return 0;
}
