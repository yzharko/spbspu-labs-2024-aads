#include "listIo.hpp"
#include "list.hpp"
#include <cctype>
#include <string>
#include <utility>

smolyakov::List<std::pair<std::string, smolyakov::List<long long>>> smolyakov::inputList(std::istream& inputStream)
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

void smolyakov::outputPairListNames(std::ostream& outputStream, List<std::pair<std::string, List<long long>>> list)
{
  if (list.isEmpty())
  {
    return;
  }

  using listOfPairs = smolyakov::List<std::pair<std::string, smolyakov::List<long long>>>;
  listOfPairs::Iterator iterator = list.begin();
  bool firstOutput = true;

  for (size_t i = 0; i < list.getSize(); i++)
  {
    if (firstOutput)
    {
      firstOutput = false;
    }
    else
    {
      outputStream << ' ';
    }

    outputStream << iterator->first;
    iterator++;
  }
  outputStream << '\n';
}
