#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <string>
#include <parser.hpp>
#include "Dictionary.hpp"
#include "cmdTree.hpp"
#include "command.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "no data!";
      return 2;
    }
    std::ifstream file;
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "file isn`t open\n";
    }
    zasulsky::cmdTree cmd;
    std::string str;
    zasulsky::Dictionary <std::string, zasulsky::Dictionary < int, std::string  > >  dicBig;
    bool isFirst = 1;
    std::string name = "";
    int key = 0;
    std::string value = "";
    if (file.peek() == std::ifstream::traits_type::eof())
    {
      std::cout << '\n';
      return 0;
    }
    while (getline(file, str))
    {
      Parser pars(str);
      zasulsky::Dictionary <int, std::string > dic;
      for (auto i = pars(); !i.empty(); i = pars())
      {
        if (isFirst)
        {
          name = i;
          isFirst = 0;
        }
        else if (isOperand(i))
        {
          key = std::stoi(i);
        }
        else
        {
          value = i;
          dic.insert(make_pair(key, value));
        }
      }
      isFirst = 1;
      dicBig.insert(make_pair(name, dic));
    }
    while (1)
    {
      std::string command;
      std::string p1;
      std::string p2;
      std::string res;
      std::string dicName;
      std::cin >> command;
      if (!std::cin)
      {
        break;
      }
      if (cmd.cmdsOne.count(command))
      {
        getline(std::cin >> std::ws, dicName);
        cmd.doCommand(dicBig, command, dicName, std::cout);
      }
      else if (cmd.cmdsTwo.count(command))
      {
        getline(std::cin >> std::ws, res, ' ');
        getline(std::cin >> std::ws, p1, ' ');
        getline(std::cin >> std::ws, p2);
        cmd.doCommand(dicBig, command, p1, p2, res);
      }
      else
      {
        printInvCmd(std::cout);
        skipUntilNewLine(std::cin);
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "bad data from user";
    return 1;
  }

}
