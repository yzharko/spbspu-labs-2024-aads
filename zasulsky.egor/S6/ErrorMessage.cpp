#include "ErrorMessage.hpp"
#include <iostream>

namespace zas
{
  void ErrorMessage(std::ostream& out)
  {
    out << "<INVALID COMMAND>\n";
  }

  void EmptyMessage(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }
}