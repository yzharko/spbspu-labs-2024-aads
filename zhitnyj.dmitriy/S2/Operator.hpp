#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "ExpressionItem.hpp"
#include <stdexcept>

class Operator : public ExpressionItem
{
public:
    explicit Operator(char op);
    ~Operator() = default;

    bool isLeftParenthesis() const;
    bool isRightParenthesis() const;
    char getOperator() const;
    int precedence() const;
    long long applyOp(long long a, long long b) const;

private:
    char operator_;

    static bool isOperator(char c);
};

#endif