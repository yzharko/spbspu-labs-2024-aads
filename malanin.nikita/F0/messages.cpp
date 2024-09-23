#include "messages.hpp"

void malanin::messages::sendInvalidCommand(std::ostream& out)
{
  out << "invalid command";
}

void malanin::messages::sendGoodbye(std::ostream& out)
{
  out << "Goodbye!";
}

