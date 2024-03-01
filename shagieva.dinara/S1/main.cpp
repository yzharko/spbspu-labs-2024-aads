#include <string>
#include "list.hpp"

int main()
{
  using pairList = shagieva::List<std::pair<std::string, shagieva::List<int>>>;
  using intList = shagieva::List<int>;
  pairList fullList;
  std::string name;
  int number = 0;

  while (std::cin >> name)
  {
    intList numbers;

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

    fullList.push_back(std::make_pair(name, numbers));
  }

  if (fullList.empty())
  {
    std::cout << 0 << "\n";
  }

  /*for (pairList::Iterator it = fullList.begin();
    it != fullList.end(); ++it)
  {
    auto & name = it.first;
    std::cout << name << " ";
  }*/

  return 0;
}
