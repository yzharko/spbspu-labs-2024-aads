#include "cmdTree.hpp"


zasulsky::CmdTree::CmdTree()
{
  cmdsOne["TAG"] = tag;
  cmdsOne["INTERSECT"] = intersect;
  cmdsOne["COMBINATION"] = combination;

  cmdsTwo["BUILD"] = build;
  cmdsTwo["PRINT"] = print;
  cmdsTwo["CALCULATE"] = calculate;

  cmdsThree["SEARCH"] = search;
  cmdsThree["TRANSLATE"] = translate;

  cmdsFour["ADD"] = add;
  cmdsFour["TRANSLATION"] = translation;

  cmdsFive["HELP"] = help;

  cmdsFive["COUNT"] = count;
}

void zasulsky::CmdTree::doCommand(const std::string& cmd,
  dictOfDicts& ref, std::string& str) const
{
  typeF function = cmdsOne.at(cmd);
  function(ref, str);
}

void zasulsky::CmdTree::doCommand(const std::string& cmd, dictOfDicts& ref, std::string str, std::ostream& out) const
{
  typeS function = cmdsTwo.at(cmd);
  function(ref, str, out);
}

void zasulsky::CmdTree::doCommand(const std::string& cmd, dictOfDicts& ref, std::string str, std::string str2, std::ostream& out) const
{
  typeT function = cmdsThree.at(cmd);
  function(ref, str, str2, out);
}

void zasulsky::CmdTree::doCommand(const std::string& cmd, dictOfDicts& ref, std::string str, std::string str2, std::string str3)
{
  typeFo function = cmdsFour.at(cmd);
  function(ref, str, str2, str3);
}
void zasulsky::CmdTree::doCommand(const std::string& cmd, dictOfDicts& ref, std::ostream& out)
{
  typeFi function = cmdsFive.at(cmd);
  function(ref, out);
}

void zasulsky::skipUntilNewLine(std::istream& in)
{
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  in.ignore(maxstream, '\n');
}

std::ostream& zasulsky::printInvCmd(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
}

void zasulsky::checkArg()
{
  if (std::cin.peek() == '\n')
  {
    throw std::invalid_argument("not correct arg");
  }
}