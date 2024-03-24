#include "list.hpp"

int main()
{
  gorbunova::List<std::pair<std::string, std::vector<int>>> sequences;
  std::string input;
  bool isEmpty = true;
  while (std::cin)
  {
    std::getline(std::cin, input);
    if (input.empty())
      break;
    isEmpty = false;
    std::string name;
    std::istringstream iss(input);
    iss >> name;
    std::vector<int> numbers;
    int num;
    while (iss >> num)
    {
      numbers.push_back(num);
    }
    sequences.push_back(std::make_pair(name, numbers));
  }
  if (isEmpty)
  {
    std::cout << "0" << std::endl;
  }
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    std::cout << (*it).first << " ";
  }
  std::cout << std::endl
            << sequences;
  size_t max_size = 0;
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    max_size = std::max(max_size, (*it).second.size());
  }
  for (size_t i = 0; i < max_size; ++i)
  {
    int sum = 0;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      if (i < (*it).second.size())
        sum += (*it).second[i];
    }
    std::cout << sum << " ";
  }
  std::cout << std::endl;
  return 0;
}
