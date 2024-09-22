#include "ioFuncs.hpp"

int main()
{
  using depot_t = proselkov::List< std::pair< std::string, proselkov::List< unsigned long long > > >;
  depot_t lines;
  size_t maxDigits = 0;

  proselkov::inputData< unsigned long long >(lines, maxDigits);
  proselkov::outOrds< unsigned long long >(lines);

  bool isOverflow = false;
  proselkov::List< unsigned long long > sums = proselkov::outDigits < unsigned long long >(lines, maxDigits, isOverflow);
  if (isOverflow)
  {
    std::cerr << "Error: Value overflow during counting the sum!\n";
    return 1;
  }
  proselkov::outSums< unsigned long long >(sums);
  return 0;
}
