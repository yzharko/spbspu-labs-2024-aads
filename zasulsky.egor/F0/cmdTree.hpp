#ifndef CMDTREE_HPP
#define CMDTREE_HPP

#include <map>
#include <string>
#include <functional>
#include "commands.hpp"

namespace zasulsky
{
  class CmdTree
  {
  public:
    CmdTree();

    void doCommand(const std::string& cmd, dictOfDicts& ref, std::string&) const;

    void doCommand(const std::string& cmd, dictOfDicts& ref, std::string, std::ostream&) const;

    void doCommand(const std::string& cmd, dictOfDicts& ref, std::string, std::string, std::ostream&) const;
    void doCommand(const std::string& cmd, dictOfDicts& ref, std::string str, std::string str2, std::string str3);
    void doCommand(const std::string& cmd, dictOfDicts& ref, std::ostream& out);


    using typeF = void(*)(dictOfDicts& ref, std::string);
    using typeS = void(*)(dictOfDicts& ref, std::string, std::ostream&);
    using typeT = void(*)(dictOfDicts& ref, std::string, std::string, std::ostream&);
    using typeFo = void(*)(dictOfDicts& ref, std::string, std::string, std::string);
    using typeFi = void(*)(dictOfDicts& ref, std::ostream& out);

    zasulsky::AVL< std::string, typeF > cmdsOne;
    zasulsky::AVL< std::string, typeS > cmdsTwo;
    zasulsky::AVL< std::string, typeT > cmdsThree;
    zasulsky::AVL< std::string, typeFo > cmdsFour;
    zasulsky::AVL< std::string, typeFi > cmdsFive;
  };
  std::ostream& printInvCmd(std::ostream& out);
  void skipUntilNewLine(std::istream& in);
  void checkArg();
}
#endif
