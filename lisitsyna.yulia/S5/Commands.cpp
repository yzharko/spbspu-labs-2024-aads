#include "commands.hpp"
#include <string>
#include "getSum.hpp"

std::pair< int, std::string > lisitsyna::ascend(AVLTree< int, std::string > & data)
{
  keySum sum;
  sum = data.traverse_lnr(sum);
  return std::make_pair(sum.get_int(), sum.get_str());
}

std::pair< int, std::string > lisitsyna::descend(AVLTree< int, std::string > & data)
{
  keySum sum;
  sum = data.traverse_rnl(sum);
  return std::make_pair(sum.get_int(), sum.get_str());
}

std::pair< int, std::string > lisitsyna::breadth(AVLTree< int, std::string > &data)
{
  keySum sum;
  sum = data.traverse_breadth(sum);
  return std::make_pair(sum.get_int(), sum.get_str());
}
