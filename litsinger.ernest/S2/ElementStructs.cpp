#include "ElementStructs.hpp"

litsinger::Operand litsinger::Operand::operator*(const litsinger::Operand & other)
{
  return Operand(operand_ * other.operand_);
}

litsinger::Operand litsinger::Operand::operator/(const litsinger::Operand & other)
{
  return Operand(operand_ / other.operand_);
}

litsinger::Operand litsinger::Operand::operator+(const litsinger::Operand & other)
{
  return Operand(operand_ + other.operand_);
}

litsinger::Operand litsinger::Operand::operator-(const litsinger::Operand & other)
{
  return Operand(operand_ - other.operand_);
}

litsinger::Operand litsinger::Operand::operator%(const litsinger::Operand & other)
{
  return Operand(operand_ % other.operand_);
}

litsinger::Element::Element():
  elem_(),
  types_(else_)
{}

litsinger::Element::Element(const Element & other):
  elem_(other.elem_),
  types_(other.types_)
{}

litsinger::type_t & litsinger::Element::getType()
{
  return types_;
}

litsinger::Operator & litsinger::Element::getOperator()
{
    return elem_.operator_;
}

litsinger::Operand & litsinger::Element::getOperand()
{
    return elem_.operand_;
}

litsinger::Bracket & litsinger::Element::getOpenBracket()
{
    return elem_.open_bracket_;
}

litsinger::Bracket & litsinger::Element::getCloseBracket()
{
  return elem_.close_bracket_;
}
