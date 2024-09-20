#ifndef OPERATOR_HPP
#define OPERATOR_HPP

namespace sadofeva
{
  struct Operator
  {
    char c;
    explicit Operator(char);

    bool operator<(const Operator & o) const noexcept;
    bool operator==(const Operator & o) const noexcept;
    bool operator<=(const Operator & o) const noexcept;
    bool isBrackets() const noexcept;
    bool isMathOperation() const noexcept;

   private:
    int getPriority_() const noexcept;
  };
}

#endif
