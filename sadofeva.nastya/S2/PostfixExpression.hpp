#ifndef POSTFIXEXPRESSION_HPP
#define POSTFIXEXPRESSION_HPP
#include "ExpressionPart.hpp"
#include "InfixExpression.hpp"
#include "queue.hpp"

namespace sadofeva
{
  class PostfixExpression
  {
   public:
    PostfixExpression() = delete;
    explicit PostfixExpression(InfixExpression);
    ~PostfixExpression() = default;

    const ExpressionPart & getNextExpressionPart() const;
    void drop();
    bool empty() const;

   private:
    Queue<ExpressionPart> expression_;
  };
}

#endif
