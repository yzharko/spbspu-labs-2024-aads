#include <deque>
#include <forward_list>
#include <list>
#include <iomanip>
#include <algorithm>
#include "sort.hpp"

namespace gorbunova
{
  void generateRandomData(std::list<int>& list, int size)
  {
    for (int i = 0; i < size; ++i)
    {
      list.push_front(rand() % 10000);
    }
  }

  void generateRandomData(std::list<double>& list, int size)
  {
    for (int i = 0; i < size; ++i)
    {
      double randomValue = static_cast<double>(rand() % 1000) + static_cast<double>(rand() % 100) / 100.0;
      list.push_front(randomValue);
    }
  }

  template <typename It>
  std::ostream& outputData(std::ostream& out, It first, It last)
  {
    while (first != last)
    {
      out << std::fixed << std::setprecision(1) << *first;
      out << (++first == last ? '\n' : ' ');
    }
    return out;
  }

  template <typename T, typename Compare>
  void executeSorting(std::ostream& out, int size, Compare comp)
  {
    std::forward_list<T> fwdList;
    std::list<T> primaryList;
    std::list<T> secondaryList;

    generateRandomData(primaryList, size);

    std::deque<T> dequeOne;
    std::deque<T> dequeTwo;
    std::deque<T> dequeThree;

    std::copy(primaryList.begin(), primaryList.end(), std::back_inserter(secondaryList));
    std::copy(primaryList.begin(), primaryList.end(), std::back_inserter(dequeOne));
    std::copy(primaryList.begin(), primaryList.end(), std::back_inserter(dequeTwo));
    std::copy(primaryList.begin(), primaryList.end(), std::back_inserter(dequeThree));
    std::copy(primaryList.begin(), primaryList.end(), std::front_inserter(fwdList));

    outputData(out, primaryList.begin(), primaryList.end());

    sortBubble(primaryList.begin(), primaryList.end(), comp);
    sortBubble(dequeOne.begin(), dequeOne.end(), comp);

    sortInsertion(secondaryList.begin(), secondaryList.end(), comp);
    sortInsertion(dequeTwo.begin(), dequeTwo.end(), comp);

    fwdList.sort(comp);

    std::sort(dequeThree.begin(), dequeThree.end(), comp);

    outputData(out, fwdList.begin(), fwdList.end());
    outputData(out, primaryList.begin(), primaryList.end());
    outputData(out, secondaryList.begin(), secondaryList.end());
    outputData(out, dequeOne.begin(), dequeOne.end());
    outputData(out, dequeTwo.begin(), dequeTwo.end());
    outputData(out, dequeThree.begin(), dequeThree.end());
  }
}
