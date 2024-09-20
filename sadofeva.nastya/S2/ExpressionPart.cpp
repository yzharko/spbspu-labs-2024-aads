#include "ExpressionPart.hpp"
#include <iostream>
#include <string>

namespace
{
  bool isNumber(const std::string & s)
  {
    if (s.empty())
    {
      return false;
    }

    if (s[0] == '-')
    {
      return s.size() > 1 && s.find_first_not_of("0123456789", 1) == s.npos;
    }
    return s.find_first_not_of("0123456789") == s.npos;
  }
}

sadofeva::ExpressionPart::ExpressionPart(std::istream & in)
{
  in >> std::skipws;
  std::string tmp;
  in >> tmp;

  if (isNumber(tmp))
  {
    operand_ = Operand{ std::stoll(tmp) };
    type_ = ExpressionPartType::OPERAND;
  }
  else if (tmp.size() == 1)
  {
    try
    {
      operator_ = Operator{ tmp[0] };
      type_ = ExpressionPartType::OPERATOR;
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      in.setstate(std::ios::failbit);
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  if (!in)
  {
    throw std::logic_error("bad reading expression part");
  }
}

sadofeva::ExpressionPart::ExpressionPart(const Operator & op):
  operator_(op),
  type_(ExpressionPartType::OPERATOR)
{}

sadofeva::ExpressionPart::ExpressionPart(const Operand & op):
  operand_(op),
  type_(ExpressionPartType::OPERAND)
{}

sadofeva::ExpressionPartType sadofeva::ExpressionPart::getType() const
{
  return type_;
}

bool sadofeva::ExpressionPart::isOperator() const noexcept
{
  return type_ == ExpressionPartType::OPERATOR;
}

bool sadofeva::ExpressionPart::isOperand() const noexcept
{
  return type_ == ExpressionPartType::OPERAND;
}

sadofeva::Operator sadofeva::ExpressionPart::getOperator() const
{
  return operator_;
}

sadofeva::Operand sadofeva::ExpressionPart::getOperand() const
{
  return operand_;
}

