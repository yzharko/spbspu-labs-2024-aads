#include "check.hpp"

bool lisitsyna::is_operator(const std::string& opr)
{
  return opr == "+" || opr == "-" || opr == "*" || opr == "/" || opr == "%";
}

int lisitsyna::get_priority(const std::string& opr)
{
  if (opr == "+" || opr == "-")
  {
    return 1;
  }
  else if (opr == "*" || opr == "/" || opr == "%")
  {
    return 2;
  }
  return 0;
}
