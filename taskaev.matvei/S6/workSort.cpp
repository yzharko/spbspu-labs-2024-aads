#include <deque>
#include <list>
#include <deque>
#include <iomanip>
#include <random>
#include <algorithm>
#include "sortFunctions.hpp"
#include "workSort.hpp"
#include <List.h>

namespace taskaev
{
  template< typename It >
  void print(const It& iter, std::ostream& out)
  {
    auto it = iter.begin();
    out << *it;
    for (auto it = ++iter.begin(); it != iter.end(); ++it)
    {
      out << " " << *it;
    }
    out << "\n";
  }

  template <typename T, typename Comparator>
  void generateData(size_t size, std::deque< T >& queue, List< T >& list)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000.0, 1000.0);

    for (size_t i = 0; i < size; ++i)
    {
      auto temp = static_cast< T >(dis(gen));
      queue.push_back(temp);
      list.pushFront(temp);
    }
  }

  template< typename T, typename Comparator >
  void workSortings(std::ostream& out, size_t size)
  {
    std::deque < T > queue;
    List< T > list;

    generatedata(size, queue, list);

    std::list< T > shakerSort(queue.begin(), queue.end());
    std::list< T > selectionSort(queue.begin(), queue.end());

    std::deque< T > sorts(queue.begin(), queue.end());
    std::deque< T > shakerS(queue.begin(), queue.end());
    std::deque< T > selectionS(queue.begin(), queue.end());

    print(queue, out);

    Shaker(shakerSort.begin(), shakerSort.end(), Comparator());
    print(shakerSort, out);

    Selection(selectionSort.begin(), selectionSort.end(), Comparator());
    print(selectionSort, out);

    std::sort(sorts.begin(), sorts.end(), Comparator());
    print(sorts, out);

    Shaker(shakerS.begin(), shakerS.end(), Comparator());
    print(shakerS, out);

    Selection(selectionS.begin(), selectionS.end(), Comparator());
    print(selectionS, out);

    Shaker(list.begin(), list.end(), Comparator());
    print(list, out);
  }
}
