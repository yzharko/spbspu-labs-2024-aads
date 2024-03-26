#include "split.hpp"
#include <cctype>

sadofeva::List< unsigned long> sadofeva::splitNumbers(const std::string & str)
{
  if (str.empty())
  {
    return {};
  }
  sadofeva::List<unsigned long > values;
  std::string str_value = "";
  auto iter = str.begin();
  while (iter!= str.end())
  {
    char c = *iter;
    ++iter;
    if(!std::isdigit(c))
    {
      if (str_value.empty())
      {
        continue;
      }
      value.push_back(std::stoul(str_value));
      str_value.clear();
    }
    else
    {
      str_value += c;
    }
  }
  if (!str_value.empty())
  {
    values.push_back(std::stoul(str_value));
  }
  return values;
}
