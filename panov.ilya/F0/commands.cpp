#include "commands.hpp"
#include <fstream>
#include <iterator>
#include <limits>

std::ostream& panov::help(std::istream& in, std::ostream& out)
{
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  return out << "help - prints out all commands\n"
    << "create <name> - create dictionary\n"
    << "add <word, name> - add word to dictionary\n"
    << "change <name> <key> <translation> - change translation\n"
    << "delete <word> <name> - delete word from dictionary\n"
    << "reset <name> - clear dictionary\n"
    << "print <name> - print dictionary contents\n"
    << "add <line> <word> - add line number to word\n"
    << "get <print> <name> <line> - get words from line\n"
    << "intersection <new_name> <name> - create new dictionary new_name from name\n"
    << "search <letter> <name> - search words by first letter\n";
}

std::ostream& panov::create(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (dicts.find(name) != dicts.end())
  {
    out << "Dict exists\n";
    throw std::logic_error("");
  }
  dict_t dict;
  dicts[name] = dict;
  return out;
}

std::ostream& panov::add(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string word;
  in >> word;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  for (const auto& entry : dicts.at(name))
  {
    if (entry.first == word)
    {
      out << "Word already exists in the dictionary\n";
      throw std::logic_error("");
    }
  }

  dicts.at(name).pushBack(std::make_pair(word, ""));
  return out;
}

std::ostream& panov::change(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string word;
  in >> word;
  std::string name;
  in >> name;
  std::string translation;
  in >> translation;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }

  for (auto& entry : dicts.at(name))
  {
    if (entry.first == word)
    {
      entry.second = translation;
      return out;
    }
  }

  out << "Word not found in the dictionary\n";
  throw std::logic_error("");
}

std::ostream& panov::reset(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  dicts.at(name).clear();
  return out;
}

std::ostream& panov::print(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("Dictionary not found");
  }

  dict_t sorted = dicts.at(name);

  for (const auto& entry : sorted)
  {
    out << entry.first << " : " << entry.second << "\n";
  }

  return out;
}

std::ostream& panov::intersection(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string newName;
  in >> newName;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  if (dicts.find(newName) != dicts.end())
  {
    out << "Dictionary with this name already exists\n";
    throw std::logic_error("Dictionary already exists");
  }
  dicts[newName] = dicts.at(name);
  return out;
}

std::ostream& panov::search(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  char letter;
  in >> letter;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }

  dict_t filteredWords;
  for (const auto& entry : dicts.at(name))
  {
    if (!entry.first.empty() && entry.first[0] == letter)
    {
      filteredWords.pushBack(entry);
    }
  }

  for (const auto& entry : filteredWords)
  {
    out << entry.first << " : " << entry.second << "\n";
  }

  return out;
}

std::ostream& panov::get(dicts_t& dicts, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  in.ignore();
  std::string line;
  std::getline(in, line);
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }

  dict_t currentDict = dicts.at(name);
  out << name << '\n';
  out << line << '\n';
  dict_t filteredWords;

  for (const auto& entry : currentDict)
  {
    if (line.find(entry.first) != std::string::npos)
    {
      filteredWords.pushBack(entry);
    }
  }

  for (const auto& entry : filteredWords)
  {
    out << entry.first << " : " << entry.second << "\n";
  }

  return out;
}

void splitWords(const std::string& str, panov::List< std::string >& words, size_t pos = 0)
{
  size_t nextSpace = str.find(' ', pos);
  if (nextSpace == std::string::npos)
  {
    words.pushBack(str.substr(pos));
  }
  else
  {
    words.pushBack(str.substr(pos, nextSpace - pos));
    splitWords(str, words, nextSpace + 1);
  }
}

std::ostream& panov::addline(std::istream& in, std::ostream& out)
{
  std::string word;
  in >> word;
  in.ignore();
  std::string line;
  std::getline(in, line);
  List< std::string > words;
  splitWords(line, words);
  List<int> indices;

  for (size_t i = 0; i < words.getSize(); ++i)
  {
    if (words[i] == word)
    {
      indices.pushBack(i);
    }
  }

  for (const auto& index : indices)
  {
    out << index << " ";
  }
  out << '\n';

  return out;
}
