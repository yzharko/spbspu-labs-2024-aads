#include <map>
#include <functional>
#include <string>
#include "funcsOfSorting.hpp"

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    mihalchenko::printWrongInput(std::cout);
    return 1;
  }
  size_t size = 0;
  if (isdigit(argv[3][0]))
  {
    size = std::stoull(argv[3]);
  }
  else
  {
    mihalchenko::printWrongSize(std::cout);
    return 1;
  }
  if (size == 0)
  {
    mihalchenko::printWrongSize(std::cout);
    return 1;
  }

  std::map<std::string, std::map<std::string, std::function<void(std::ostream &, int)>>> functions{};
  {
    using namespace std::placeholders;
    functions["ints"]["ascending"] = std::bind(mihalchenko::sortData<int, std::less<int>>, _1, _2, std::less<int>());
    functions["ints"]["descending"] = std::bind(mihalchenko::sortData<int, std::greater<int>>, _1, _2, std::greater<int>());
    functions["floats"]["ascending"] = std::bind(mihalchenko::sortData<double, std::less<double>>, _1, _2, std::less<double>());
    functions["floats"]["descending"] = std::bind(mihalchenko::sortData<double, std::greater<double>>, _1, _2, std::greater<double>());
  }

  try
  {
    functions.at(argv[2]).at(argv[1])(std::cout, size);
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "Error: wrong parameter\n";
    return 1;
  }

  return 0;
}
