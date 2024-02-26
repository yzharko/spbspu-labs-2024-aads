#include <string>
#include "list.hpp"

int main()
{
  /*std::string seqName = 0;
  std::cin >> seqName;
  if (!std::cin)
  {
    std::cout << 0 << "\n";
    return 0;
  }*/

  if (!std::cin)
  {
    std::cout << 0 << "\n";
    return 0;
  }

  std::string seqName, num;
  shagieva::List< std::pair<std::string, shagieva::List<int>> > fullList;
  std::string name;
  int number;

  while (std::cin >> name)
  {
    shagieva::List<int> numbers;
    fullList.push_back(std::make_pair(name, numbers));

    if (std::cin.peek() == '\n')
    {
      continue;
    }

    while (std::cin >> number)
    {
      if (std::cin.peek() == '\n')
      {
        numbers.push_back(number);
        break;
      }
      numbers.push_back(number);
    }
  }

  if (fullList.empty())
  {
    std::cout << 0 << "\n";
  }
  return 0;
}
