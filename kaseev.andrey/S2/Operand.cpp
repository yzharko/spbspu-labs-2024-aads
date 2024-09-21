#include "Operand.hpp"

kaseev::Operand::Operand(long long val) : value(val)
{}

long long kaseev::Operand::getValue()
{
  return value;
}

bool kaseev::Operand::isOperator()
{
  return false;
}

bool kaseev::Operand::isOperand()
{
  return true;
}