#include <map>
#include <string>
#include <functional>
#include "sortFuncs.hpp"
#include "utils.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    proselkov::outWrongParams(std::cout);
    return 1;
  }

  size_t size = 0;
  if (argv[3][0] == '-')
  {
    proselkov::outWrongParams(std::cout);
    return 1;
  }

  try
  {
    size = std::stoull(argv[3]);
  }
  catch (const std::invalid_argument&)
  {
    proselkov::outWrongSize(std::cout);
    return 1;
  }

  if (size == 0)
  {
    proselkov::outWrongSize(std::cout);
    return 2;
  }

  std::map< std::string, std::map < std::string, std::function< void(std::ostream&, size_t) > > > sortFuncs;
  {
    using namespace std::placeholders;
    sortFuncs["ints"]["ascending"] = std::bind(proselkov::makeSorted< int, std::less< int > >, _1, _2, std::less< int >());
    sortFuncs["ints"]["descending"] = std::bind(proselkov::makeSorted< int, std::greater< int > >, _1, _2, std::greater< int >());

    sortFuncs["floats"]["ascending"] = std::bind(proselkov::makeSorted< double, std::less< double > >, _1, _2, std::less< double >());
    sortFuncs["floats"]["descending"] = std::bind(proselkov::makeSorted< double, std::greater< double > >, _1, _2, std::greater< double >());
  }

  std::string sortDirect = argv[1];
  std::string dataType = argv[2];

  if (sortFuncs.find(dataType) == sortFuncs.end())
  {
    proselkov::outWrongParams(std::cout);
    return 1;
  }

  try
  {
    sortFuncs.at(dataType).at(sortDirect)(std::cout, size);
  }
  catch (const std::out_of_range&)
  {
    proselkov::outWrongParams(std::cout);
    return 1;
  }

  return 0;
}
