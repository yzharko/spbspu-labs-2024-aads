#include "listIo.hpp"
#include "list.hpp"
#include <cctype>
#include <string>
#include <utility>

smolyakov::List<std::pair<std::string, smolyakov::List<long long>>> smolyakov::InputList(std::istream& inputStream)
{
  std::string rawInput = "";
  long long inputNumber = 0;
  smolyakov::List<std::pair<std::string, smolyakov::List<long long>>> list;

  while (inputStream >> rawInput)
  {
    if (std::isalpha(rawInput[0]))
    {
      list.pushBack({rawInput, List<long long>()});
    }
    else
    {
      inputNumber = std::stoll(rawInput);
      list.end()->second.pushBack(inputNumber);
    }
  }
  return list;
}
