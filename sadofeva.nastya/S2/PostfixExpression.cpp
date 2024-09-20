#include "PostfixExpression.hpp"
#include "ExpressionPart.hpp"
#include "stack.hpp"

sadofeva::PostfixExpression::PostfixExpression(InfixExpression infix_expression):
  expression_{}
{
  Stack<ExpressionPart> stack;

  while (!infix_expression.empty())
  {
    ExpressionPart part = infix_expression.getNextExpressionPart();
    infix_expression.drop();

    if (part.isOperator())
    {
      if (part.getOperator() == Operator('('))
      {
        stack.push(part);
      }
      else if (part.getOperator() == Operator(')'))
      {
        while (!stack.empty() && stack.top().getOperator().isMathOperation())
        {
          expression_.push(stack.top());
          stack.drop();
        }
        if (!stack.empty() && stack.top().isOperator() && stack.top().getOperator() == Operator('('))
        {
          stack.drop();
        }
      }
      else if (part.getOperator().isMathOperation())
      {
        Operator op = part.getOperator();
        while (!stack.empty() && stack.top().getOperator().isMathOperation() && op <= stack.top().getOperator())
        {
          expression_.push(stack.top());
          stack.drop();
        }
        stack.push(part);
      }
    }
    else if (part.isOperand())
    {
      expression_.push(part);
    }
  }
  while (!stack.empty())
  {
    expression_.push(stack.top());
    stack.drop();
  }
}

const sadofeva::ExpressionPart & sadofeva::PostfixExpression::getNextExpressionPart() const
{
  return expression_.next();
}

void sadofeva::PostfixExpression::drop()
{
  expression_.drop();
}

bool sadofeva::PostfixExpression::empty() const
{
  return expression_.empty();
}

