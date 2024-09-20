#ifndef ERRORMESSAGE_HPP
#define ERRORMESSAGE_HPP
#include <iosfwd>

namespace zas
{
  void ErrorMessage(std::ostream& out);
  void EmptyMessage(std::ostream& out);
}

#endif
