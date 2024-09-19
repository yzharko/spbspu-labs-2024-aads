#ifndef CMDTREE_HPP
#define CMDTREE_HPP

#include <string>
#include <functional>
#include <ostream>
#include "command.hpp"
#include "Dictionary.hpp"
#include "AVL.hpp"

namespace zasulsky
{
  class cmdTree
  {
    using ps = Dictionary< std::string, Dictionary< int, std::string > >;

  public:
    Dictionary < std::string, void(*)(ps&, std::string, std::ostream&) >  cmdsOne;
    Dictionary < std::string, void(*)(ps&, std::string, std::string, std::string) > cmdsTwo;

    cmdTree()
    {
      cmdsOne["print"] = print;
      cmdsTwo["union"] = getUnion;
      cmdsTwo["intersect"] = intersect;
      cmdsTwo["complement"] = complement;
    }

    void doCommand(ps& ref, std::string cmd, std::string name, std::ostream& out)
    {
      void(*function)(ps&, std::string, std::ostream&) = cmdsOne[cmd];
      function(ref, name, out);
    }
    void doCommand(ps& ref, std::string cmd, std::string p1, std::string p2, std::string res)
    {
      void(*function)(ps&, std::string, std::string, std::string) = cmdsTwo[cmd];
      function(ref, p1, p2, res);
    }

  };
}

#endif
