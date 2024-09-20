#ifndef EXPRESSION_PART_HPP
#define EXPRESSION_PART_HPP

#include <iosfwd>

#include "Operator.hpp"
#include "Operand.hpp"

namespace sadofeva
{
  enum class ExpressionPartType
  {
    OPERATOR,
    OPERAND
  };

  struct ExpressionPart
  {
   public:
    ExpressionPart() = delete;

    ExpressionPart(std::istream & in);

    explicit ExpressionPart(const Operator & op);
    explicit ExpressionPart(const Operand & op);

    ~ExpressionPart() = default;

    ExpressionPartType getType() const;

    bool isOperator() const noexcept;
    bool isOperand() const noexcept;

    Operator getOperator() const;
    Operand getOperand() const;

   private:
    union
    {
      Operator operator_;
      Operand operand_;
    };
    ExpressionPartType type_;
  };
}

#endif
