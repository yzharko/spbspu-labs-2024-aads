#include <iostream>
#include <functional>
#include "commands.hpp"

int main()
{
  setlocale(LC_ALL, "Russian");

  using mapDictionaries_t = litsinger::AvlTree< std::string, litsinger::AvlTree< std::string, litsinger::List< size_t > > >;

  mapDictionaries_t mapDictionaries;

  using namespace std::placeholders;
  litsinger::AvlTree< std::string, std::function < void(mapDictionaries_t&, std::istream&, std::ostream&) > > command;
  {
    command.emplace("help", std::bind(litsinger::printCommands, _3));
    command.emplace("create", litsinger::creatDict);
    command.emplace("add_word", litsinger::addWord);
    command.emplace("delete_word", litsinger::deleteWord);
    command.emplace("reset", litsinger::resetDict);
    command.emplace("print", litsinger::printDict);
    command.emplace("add_line", litsinger::addLine);
    command.emplace("get_print", litsinger::getPrint);
    command.emplace("get_intersection", litsinger::getIntersection);
    command.emplace("search_letter", litsinger::searchLetter);
  }

  std::string cmd = "";

  std::cout << "Введите любую допустимую команду (команда 'help' для вывода всех доступных команд).\n";
  while (std::cin >> cmd)
  {
    try
    {
      command.at(cmd)(mapDictionaries, std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  return 0;
}