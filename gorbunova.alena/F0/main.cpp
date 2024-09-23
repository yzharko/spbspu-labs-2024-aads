#include <iostream>
#include "commands.hpp"

int main()
{
  gorbunova::help();
  std::string command;

  while (true)
  {
    std::cout << "Enter command: ";
    std::cin >> command;

    if (command == "exit")
      break;

    if (command == "create")
    {
      std::string name;
      std::cin >> name;
      gorbunova::create(name);
    }
    else if (command == "remove")
    {
      std::string name;
      std::cin >> name;
      gorbunova::remove(name);
    }
    else if (command == "clear")
    {
      std::string name;
      std::cin >> name;
      gorbunova::clear(name);
    }
    else if (command == "print")
    {
      std::string name;
      std::cin >> name;
      gorbunova::print(name);
    }
    else if (command == "size")
    {
      std::string name;
      std::cin >> name;
      gorbunova::size(name);
    }
    else if (command == "list")
    {
      gorbunova::list();
    }
    else if (command == "unite")
    {
      std::string newName, name1, name2;
      std::cin >> newName >> name1 >> name2;
      gorbunova::unite(newName, name1, name2);
    }
    else if (command == "add")
    {
      std::string name1, name2;
      std::cin >> name1 >> name2;
      gorbunova::add(name1, name2);
    }
    else if (command == "intersection")
    {
      std::string newName, name1, name2;
      std::cin >> newName >> name1 >> name2;
      gorbunova::intersection(newName, name1, name2);
    }
    else if (command == "insert")
    {
      std::string name, key, translation;
      std::cin >> name >> key >> translation;
      gorbunova::insert(name, key, translation);
    }
    else if (command == "find")
    {
      std::string name, key;
      std::cin >> name >> key;
      gorbunova::find(name, key);
    }
    else if (command == "change")
    {
      std::string name, key, translation;
      std::cin >> name >> key >> translation;
      gorbunova::change(name, key, translation);
    }
    else if (command == "findLetter")
    {
      std::string name;
      char letter;
      std::cin >> name >> letter;
      gorbunova::findLetter(name, letter);
    }
    else if (command == "delete")
    {
      std::string name, key;
      std::cin >> name >> key;
      gorbunova::deleteElem(name, key);
    }
    else
    {
      std::cout << "Unknown command. Type 'help' for the list of commands.\n";
    }
  }

  return 0;
}
