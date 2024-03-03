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

  for (pairList::Iterator it = fullList.begin();
    it != fullList.end(); ++it)
  {
    auto & name = it.curr->data.first;
    std::cout << name << " ";
  }
  std::cout << "\n";

  for (pairList::Iterator it = fullList.begin();
    it != fullList.end(); ++it)
  {
    auto numbers = it.curr->data.second;
    for (intList::Iterator it = numbers.begin();
      it != numbers.end(); ++it)
    {
      auto & number = it.curr->data;
      std::cout << name << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  return 0;
}
