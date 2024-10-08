#include <iostream>
#include <utility>
#include "AVL.hpp"
#include "cmdTree.hpp"
#include "vector.hpp"


int main()
{
  dictOfDicts dic;
  zasulsky::CmdTree cmd;
  while (!std::cin.eof())
  {
    std::string command = "";
    std::cin >> command;
    if (!std::cin)
    {
      break;
    }
    try
    {
      if (cmd.cmdsOne.count(command))
      {
        std::string str;
        std::getline(std::cin, str);
        cmd.doCommand(command, dic, str);
      }
      else if (cmd.cmdsTwo.count(command))
      {
        std::string str;
        std::cin >> str;
        cmd.doCommand(command, dic, str, std::cout);
      }
      else if (cmd.cmdsThree.count(command))
      {
        std::string str;
        std::string str2;
        std::cin >> str;
        std::cin >> str2;
        cmd.doCommand(command, dic, str, str2, std::cout);
      }
      else if (cmd.cmdsFour.count(command))
      {
        std::string str;
        std::string str2;
        std::string str3;
        std::string str22;
        std::cin >> str;
        zasulsky::checkArg();
        std::getline(std::cin >> std::ws, str2, '-');
        std::cin >> str3;
        cmd.doCommand(command, dic, str, str2, str3);
      }
      else if (cmd.cmdsFive.count(command))
      {
        cmd.doCommand(command, dic, std::cout);
      }
      else
      {
        zasulsky::printInvCmd(std::cout);
      }
    }
    catch (...)
    {
      zasulsky::printInvCmd(std::cout);
      std::cin.clear();
      zasulsky::skipUntilNewLine(std::cin);
      continue;
    }
  }
}
