#ifndef EXPRESSION_CALCULATION_HPP
#define EXPRESSION_CALCULATION_HPP
#include <iosfwd>
#include "InfixExpression.hpp"
#include "PostfixExpression.hpp"

namespace sadofeva
{
  Queue<InfixExpression> readExpressions(std::istream & in);
  long long calculatePostfixExpression(PostfixExpression expression);
}

#endif

