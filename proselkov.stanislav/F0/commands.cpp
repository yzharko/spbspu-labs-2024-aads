#include "commands.hpp"

#include <iostream>
#include <fstream>

namespace proselkov
{
  void print(langDictionary& dict, std::ostream& out)
  {
    if (dict.isEmpty())
    {
      out << "<EMPTY>\n";
    }
    else
    {
      auto beginMinIt = dict.cbegin();
      auto endMinIt = dict.cend();
      while (beginMinIt != endMinIt)
      {
        out << beginMinIt->first << '-' << beginMinIt->second << '\n';
        beginMinIt++;
      }
    }
  }
}

void proselkov::helpCmd(std::istream& in, std::ostream& out)
{
  out << "Список команд:\n"
    << "1. help - вывод списка всех доступных команд и их описание.\n"
    << "2. create <name> - создание словаря с именем name.\n"
    << "3. remove <name> - удаление словаря с именем name.\n"
    << "4. print <name> - вывод содержимого словаря с именем name."
    "Если словарь пуст, то команда выводит сообщение <EMPTY>.\n"
    << "5. clear <name> - очистка содержимого словаря с именем name.\n"
    << "6. delete <name> <word> - удаление слова word из словаря с именем name.\n"
    << "7. insert <name> <word> - добавление слова word в словарь с именем name.\n"
    << "8. search <name> <word> - поиск слова word в словаре"
    "с именем name с выводом его перевода.\n"
    << "9. size <name> - вывод размера (количества слов) словаря name.\n"
    << "10. edit <name> <key> <translation> - присвоить"
    "значение (перевод) translation слову key.\n"
    << "11. combine <name1> <name2> <new_name> - создание нового словаря"
    "new_name с объединением всех слов из словарей name1 и name2.\n"
    << "12. save <name> <название_файла> - сохранить словарь"
    "с именем name в файл с расширением txt.\n";
}

void proselkov::createCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  if (!major.isEmpty() && major.find(dictName) != major.end())
  {
    throw std::invalid_argument("dictionary already exists");
  }

  langDictionary newDict;
  major.insert(std::make_pair(dictName, newDict));
}

void proselkov::removeCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  major.erase(dictName);
}

void proselkov::printCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  print(majIt->second, out);
}

void proselkov::clearCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  majIt->second.clear();
}

void proselkov::deleteCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  majIt->second.erase(word);
}

void proselkov::insertCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  if (majIt->second.find(word) != majIt->second.end())
  {
    throw std::invalid_argument("this word already exists");
  }
  majIt->second.insert(std::make_pair(word, std::string()));
}

void proselkov::searchCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  std::string word;
  in >> dictName >> word;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  auto minIt = majIt->second.find(word);
  if (minIt == majIt->second.end())
  {
    throw std::invalid_argument("this word doesn't exist");
  }
  out << minIt->first << '-' << minIt->second << '\n';
}

void proselkov::sizeCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  out << majIt->second.getSize() << '\n';
}

void proselkov::editCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  std::string wordEng;
  std::string wordRus;
  in >> dictName >> wordEng >> wordRus;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }
  auto minIt = majIt->second.find(wordEng);
  if (minIt == majIt->second.end())
  {
    throw std::invalid_argument("this word doesn't exist");
  }
  minIt->second = wordRus;
}

void proselkov::combineCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string firstName;
  std::string secondname;
  std::string newName;
  in >> firstName >> secondname >> newName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  if (firstName == secondname)
  {
    throw std::invalid_argument("same dictionaries");
  }
  auto firstIt = major.find(firstName);
  if (firstIt == major.end())
  {
    throw std::invalid_argument("first dictionary doesn't exist");
  }
  auto secondIt = major.find(secondname);
  if (secondIt == major.end())
  {
    throw std::invalid_argument("second dictionary doesn't exist");
  }
  langDictionary newDict;
  auto firstMinIt = firstIt->second.begin();
  while (firstMinIt != firstIt->second.end())
  {
    newDict.insert(*firstMinIt);
    firstMinIt++;
  }
  auto secondMinIt = secondIt->second.begin();
  while (secondMinIt != secondIt->second.end())
  {
    if (newDict.find(secondMinIt->first) == newDict.end())
    {
      newDict.insert(*secondMinIt);
    }
    secondMinIt++;
  }
  major.insert(std::make_pair(newName, newDict));
}

void proselkov::saveCmd(majorDictionary& major, std::istream& in, std::ostream& out)
{
  std::string dictName;
  std::string fileName;
  in >> dictName >> fileName;
  if (!in)
  {
    throw std::invalid_argument("invalid name");
  }

  auto majIt = major.find(dictName);
  if (majIt == major.end())
  {
    throw std::invalid_argument("this dictionary doesn't exist");
  }

  std::ofstream file(fileName);
  print(majIt->second, file);
}
