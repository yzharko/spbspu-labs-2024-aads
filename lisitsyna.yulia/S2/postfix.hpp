#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include <string>
#include "queue.hpp"
#include "stack.hpp"

namespace lisitsyna
{
  void calculate_postfix(Queue< std::string > & result_queue, Stack< long long int > & operands);
}

#endif
