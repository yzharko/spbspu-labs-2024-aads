#include <iostream>
#include <string>

#include "task.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong program args\n";
    return 1;
  }

  std::string sort = argv[1];
  std::string type = argv[2];
  size_t N = std::stoull(argv[3]);

  if (sort != "ascending" && sort != "descending")
  {
    std::cerr << "Wrong sort type arg\n";
    return 3;
  }

  if (type == "ints")
  {
    if (sort == "ascending")
    {
      sadofeva::task<int, std::less<int>>(N);
    }
    else
    {
      sadofeva::task<int, std::greater<int>>(N);
    }
  }
  else if (type == "floats")
  {
    if (sort == "ascending")
    {
      sadofeva::task<float, std::less<float>>(N);
    }
    else
    {
      sadofeva::task<float, std::greater<float>>(N);
    }
  }
  else
  {
    std::cerr << "Wrong type arg\n";
    return 2;
  }

  return 0;
}
