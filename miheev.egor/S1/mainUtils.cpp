#include "mainUtils.hpp"
#include "stdexcept"

namespace miheev
{
  size_t readInt(std::istream& stream)
  {
    size_t number = 0;
    if (!(stream >> number))
    {
      throw std::logic_error("Cant process number on input\n");
    }
    return number;
  }

  List< size_t > readNumbers(std::istream& stream)
  {
    if ((stream >> std::ws).eof())
    {
      List< size_t > list;
      return list;
    }
    List< size_t > list(readInt(stream));

    while(!(stream >> std::ws).eof())
    {
      list.pushBack(readInt(stream));
    }
    return list;
  }

  SI_pair getSIPair(std::istream& stream)
  {
    SI_pair pair;
    stream >> pair.first; // reading word
    pair.second = readNumbers(stream);
    return pair;
  }

  ListIter* getIters(SI_pair* pairs, size_t size)
  {
    ListIter* iters = new ListIter[size];
    for (size_t i = 0; i < size; i++)
    {
      iters[i] = ListIter(pairs[i].second.begin());
    }
    return iters;
  }

  List< size_t >* getLists(SI_pair* pairs, size_t size)
  {
    List< size_t >* lists = new List< size_t > [size];
    for (size_t i = 0; i < size; i++)
    {
      lists[i] = pairs[i].second;
    }
    return lists;
  }

  size_t maxListSize(List< size_t >* lists, size_t size)
  {
    size_t max = lists[0].size();
    for (size_t i = 0; i < size; i++)
    {
      List< size_t > list = lists[i];
      size_t size = list.size();
      if (size > max)
      {
        max = size;
      }
    }
    return max;
  }
}
