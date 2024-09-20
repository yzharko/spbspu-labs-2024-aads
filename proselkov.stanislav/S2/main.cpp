#include <fstream>
#include "termFuncs.hpp"

int main(int argc, char* argv[])
{
  proselkov::Queue< std::string > terms;
  proselkov::Stack< long long > results;

  if (argc == 1)
  {
    proselkov::readTerms(std::cin, terms);
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    proselkov::readTerms(input, terms);
  }
  else
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 1;
  }
  try
  {
    proselkov::makeResults(terms, results);
    while (!results.isEmpty())
    {
      std::cout << results.getTop();
      results.pop();
      if (!results.isEmpty())
      {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cout << e.what();
    return 1;
  }
  return 0;
}
