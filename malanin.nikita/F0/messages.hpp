#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <iostream>

namespace malanin
{
  namespace messages
  {
    void sendInvalidCommand(std::ostream&);
    void sendGoodbye(std::ostream&);
  }

  template< typename Printer, typename... Args >
  void errorWrapper(std::ostream&, Printer p, Args... args);

  template< typename Printer, typename... Args >
  void infoWrapper(std::ostream&, Printer p, Args... args);

  template< typename Printer, typename... Args >
  void exitWrapper(std::ostream&, Printer p, Args... args);
}

template< typename Printer, typename... Args >
void malanin::errorWrapper(std::ostream& out, Printer p, Args... args)
{
  out << "[ERROR] ";
  p(out, args...);
  out << '\n';
}

template< typename Printer, typename... Args >
void malanin::infoWrapper(std::ostream& out, Printer p, Args... args)
{
  out << "[INFO] ";
  p(out, args...);
  out << '\n';
}

template< typename Printer, typename... Args >
void malanin::exitWrapper(std::ostream& out, Printer p, Args... args)
{
  out << "[EXIT] ";
  p(out, args...);
  out << '\n';
}

#endif


