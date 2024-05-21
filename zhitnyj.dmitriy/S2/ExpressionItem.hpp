#ifndef EXPRESSION_ITEM_HPP
#define EXPRESSION_ITEM_HPP

class ExpressionItem
{
public:
    virtual ~ExpressionItem() = default;

    virtual bool isOperator() = 0;
    virtual bool isOperand() = 0;
};

#endif
