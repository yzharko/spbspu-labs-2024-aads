#include <iostream>
#include <string>
#include "sorting.hpp"
#include "func.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 4)
    {
      throw std::invalid_argument("not corrent quantity of arguments");
    }
    std::string arg1 = argv[1];
    std::string arg2 = argv[2];
    std::string arg3 = argv[3];
    int cal = stoi(arg3);
    if (arg1 != "ascending" && arg1 != "descending")
    {
      throw std::invalid_argument("not correct arg");
    }

    bool order = (arg1 == "ascending") ? true : false;
    if (arg2 == "ints")
    {
      processContainers<int>(cal, order);
    }
    else if (arg2 == "floats")
    {
      processContainers<float>(cal, order);
    }
    else
    {
      throw std::invalid_argument("not correct arg");
    }
  }
  catch (...)
  {
    std::cerr << "not correct arg";
    return 1;
  }
}
