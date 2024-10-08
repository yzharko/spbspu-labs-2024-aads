#ifndef TOINFIX_HPP
#define TOINFIX_HPP

#include <string>
#include <iostream>
#include "queue.hpp"

namespace lisitsyna
{
  void input_infix(std::istream & input, Queue< Queue< std::string > > & input_queue);
  void to_postfix(Queue< std::string > & process_queue, Queue< std::string > & result_queue);
}

#endif
