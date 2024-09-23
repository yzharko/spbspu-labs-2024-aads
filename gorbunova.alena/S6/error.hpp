#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <iosfwd>

namespace gorbunova
{
  std::ostream& displayParameterError(std::ostream& out);
  std::ostream& displaySizeError(std::ostream& out);
}

#endif
