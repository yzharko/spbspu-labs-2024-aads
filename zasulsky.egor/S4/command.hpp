#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <limits>
#include "Dictionary.hpp"


void print(Dictionary < std::string, Dictionary < int, std::string > >& dicBig, std::string name, std::ostream& out);

void intersect(Dictionary < std::string, Dictionary < int, std::string >>& dicBig, std::string p1, std::string p2, std::string res);

void complement(Dictionary < std::string, Dictionary < int, std::string> >& dicBig, std::string p1, std::string p2, std::string res);

void getUnion(Dictionary < std::string, Dictionary < int, std::string > >& dicBig, std::string p1, std::string p2, std::string res);

std::ostream& printInvCmd(std::ostream& out);

void skipUntilNewLine(std::istream& in);

bool isOperand(std::string st);


#endif
