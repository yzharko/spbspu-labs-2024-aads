#include "parser.hpp"
#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"

zasulsky::Parser::Parser(std::string toparse) :
  parsable_(toparse),
  current_(toparse.find_first_not_of(" "))
{}

std::string zasulsky::Parser::operator ()()
{
  if (current_ > parsable_.length())
  {
    return "";
  }
  size_t start = current_;
  size_t end = 0;
  auto che = parsable_.substr(current_).find_first_of(" ");
  if (che == std::string::npos)
  {
    end = parsable_.length();
  }
  else
  {
    end = current_ + parsable_.substr(current_).find_first_of(" ");
  }
  current_ = 1 + end;
  return parsable_.substr(start, end - start);
}


