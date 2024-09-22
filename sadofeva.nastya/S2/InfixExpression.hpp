#ifndef INFIXEXPRESSION_HPP
#define INFIXEXPRESSION_HPP

#include <iosfwd>

#include "ExpressionPart.hpp"
#include "queue.hpp"

namespace sadofeva
{
  class InfixExpression
  {
   public:
    InfixExpression(std::istream & in);
    ~InfixExpression() = default;

    const ExpressionPart & getNextExpressionPart() const;
    void drop();
    bool empty() const;

   private:
    Queue<ExpressionPart> eparts_;
  };
}

#endif
