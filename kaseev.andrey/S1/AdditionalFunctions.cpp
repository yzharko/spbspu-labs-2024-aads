#include "AdditionalFunctions.hpp"
#include "sstream"

namespace kaseev {
  int readList(const std::string &line, kaseev::List<std::pair<std::string, kaseev::List<int>>> &arr)
  {
    std::istringstream iss(line);
    std::string ListName;
    if (!(iss >> ListName))
    {
      std::cerr << "Empty line! \n";
      return 1;
    }
    kaseev::List<int> tempList;
    int num;
    try
    {
      while (iss >> num)
      {
        tempList.pushBack(num);
      }
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "List size exceeds maximum limit";
      return 0;
    }
    std::pair<std::string, kaseev::List<int>> list_pair;
    list_pair.first = ListName;
    list_pair.second = tempList;
    arr.pushBack(list_pair);
    return 0;
  }


  int sumNumbersInString(const std::string &line)
  {
    std::istringstream iss(line);
    int sum = 0;
    int num;
    while (iss >> num)
    {
      sum += num;
    }
    return sum;
  }

  void sumNumbersInArray(const kaseev::List<std::pair<std::string, kaseev::List<int>>> &sums)
  {
    for (int i = 0; i < sums.size(); ++i)
    {
      const auto &pair = sums[i];
      const std::string &line = pair.first;
      int sum = 0;
      sum = sumNumbersInString(line);
      std::cout << sum << " ";
    }
    std::cout << "\n";
  }
}
