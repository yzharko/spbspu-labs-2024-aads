#include "Keystruct.hpp"
#include <limits>
#include <stdexcept>


sadofeva::KeyVal::KeyVal() :
  keySum_(0),
  valSum_("")
{};

void sadofeva::KeyVal::operator()(const std::pair< const int, std::string >& keyval)
{
  int maximum = std::numeric_limits< int >::max();
  int minimum = std::numeric_limits< int >::min();
  if (keyval.first > 0 && maximum - keySum_ < keyval.first)
  {
    throw std::out_of_range("<OUT OF RANGE>\n");
  }
  if (keyval.first < 0 && minimum - keySum_ > keyval.first)
  {
    throw std::out_of_range("<OUT OF RANGE>\n");
  }
  keySum_ += keyval.first;
  if (!valSum_.empty())
  {
    valSum_ += " ";
  }
  valSum_ += keyval.second;
}

int sadofeva::KeyVal::get_key_sum() const
{
  return keySum_;
}

std::string sadofeva::KeyVal::get_val_sum()
{
  return valSum_;
}
