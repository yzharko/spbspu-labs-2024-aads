#ifndef FUNC_HPP
#define FUNC_HPP

#include <vector>
#include <deque>
#include <list>
#include <ForwardList.hpp>
#include <vector>

float randomFloat()
{
  const float min = -1000.0f;
  const float max = 1000.0f;
  return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

template <typename T>
void fillContainers(int count, std::vector<T>& vec, zasulsky::ForwardList<T>& fL, std::deque<T>& deque, std::list<T>& l, std::list<T>& l2)
{
  for (int i = 0; i < count; i++)
  {
    vec.push_back(static_cast<T>(rand()));
  }

  for (const auto& elem : vec) {
    fL.insert_after(fL.before_begin(), elem);
  }

  std::copy(vec.begin(), vec.end(), std::back_inserter(deque));
  std::copy(vec.begin(), vec.end(), std::back_inserter(l));
  std::copy(vec.begin(), vec.end(), std::back_inserter(l2));
}

template <typename T>
void fillContainersF(int count, std::vector<T>& vec, zasulsky::ForwardList<T>& fL, std::deque<T>& deque, std::list<T>& l, std::list<T>& l2)
{
  for (int i = 0; i < count; i++)
  {
    vec.push_back(static_cast<T>(randomFloat()));
  }

  for (const auto& elem : vec) {
    fL.insert_after(fL.beforeBegin(), elem);
  }

  std::copy(vec.begin(), vec.end(), std::back_inserter(deque));
  std::copy(vec.begin(), vec.end(), std::back_inserter(l));
  std::copy(vec.begin(), vec.end(), std::back_inserter(l2));
}


template <typename T>
void printContainers(const zasulsky::ForwardList<T>& fL, const std::deque<T>& deque, const std::list<T>& l, const std::list<T>& l2)
{
  std::copy(fL.begin(), fL.end(), std::ostream_iterator<T>(std::cout, " "));
  std::cout << '\n';

  std::copy(deque.begin(), deque.end(), std::ostream_iterator<T>(std::cout, " "));
  std::cout << '\n';

  std::copy(l.begin(), l.end(), std::ostream_iterator<T>(std::cout, " "));
  std::cout << '\n';

  std::copy(l2.begin(), l2.end(), std::ostream_iterator<T>(std::cout, " "));
  std::cout << '\n';
}

template <typename T>
void outputOldData(std::vector<T>& vec)
{
  for (size_t i = 0; i < vec.size(); i++)
  {
    std::cout << vec[i];
    if (i == vec.size() - 1)
    {
      std::cout << '\n';
    }
    else
    {
      std::cout << ' ';
    }
  }
}

template< typename T >
void processContainers(int cal, bool order)
{
  zasulsky::ForwardList<T > forwardList;
  std::deque<T> deque;
  std::list<T> list;
  std::list<T> list2;
  std::vector<T> vec;
  fillContainersF(cal, vec, forwardList, deque, list, list2);
  outputOldData(vec);

  sortBubble(forwardList, order);
  shellSort(deque, order);
  sortBubble(list, order);
  sortBubble(list2, order);

  printContainers(forwardList, deque, list, list2);
}

#endif
