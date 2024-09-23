#include <iostream>
#include "list.hpp"

namespace gorbunova
{
  List<std::pair<std::string, List<std::pair<std::string, std::string>>>> dictionaries;
  using Dictionary = List<std::pair<std::string, std::string>>;

  void help()
  {
    std::cout << "Available commands:\n"
      << "help - display the list of available commands\n"
      << "create <name> - create a dictionary with the name <name>\n"
      << "remove <name> - delete the dictionary with the name <name>\n"
      << "clear <name> - clear the dictionary with the name <name>\n"
      << "print <name> - display the contents of the dictionary <name>\n"
      << "size <name> - count the number of words in the dictionary <name>\n"
      << "list - display the list of all dictionaries\n"
      << "unite <newName> <name1> <name2> - merge dictionaries <name1> and <name2>"
      << "into a new dictionary <newName>\n"
      << "add <name1> <name2> - add dictionary <name1> to dictionary <name2>\n"
      << "intersection <newName> <name1> <name2> - intersect dictionaries <name1> and <name2>"
      << "into a new dictionary <newName>\n"
      << "insert <name> <key> <translation> - insert an element into dictionary <name>\n"
      << "find <name> <key> - find the translation of the key in dictionary <name>\n"
      << "change <name> <key> <translation> - modify the translation of an element in dictionary <name>\n"
      << "findLetter <name> <letter> - find words by the first letter in dictionary <name>\n"
      << "delete <name> <key> - remove the element with the key from dictionary <name>\n"
      << "exit - exit the program\n";
  }
  void create(const std::string& name)
  {
    dictionaries.push_back({ name, List<std::pair<std::string, std::string>>() });
    std::cout << "Dictionary " << name << " created." << std::endl;
  }

  void remove(const std::string& name)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        dictionaries.erase(it);
        std::cout << "Dictionary \"" << name << "\" removed." << std::endl;
        return;
      }
    }
    std::cout << "Dictionary \"" << name << "\" not found." << std::endl;
  }

  void clear(const std::string& name)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        it->second.clear();
        std::cout << "Dictionary \"" << name << "\" cleared." << std::endl;
        return;
      }
    }
    std::cout << "Dictionary " << name << "not found." << std::endl;
  }

  void print(const std::string& name)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        std::cout << "Dictionary \"" << name << "\":" << std::endl;
        for (auto entryIt = it->second.begin(); entryIt != it->second.end(); ++entryIt)
        {
          std::cout << entryIt->first << ": " << entryIt->second << std::endl;
        }
        return;
      }
    }
    std::cout << "Dictionary " << name << " not found." << std::endl;
  }

  void size(const std::string& name)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        std::cout << "Size of dictionary " << name << ": " << it->second.getSize() << std::endl;
        return;
      }
    }
    std::cout << "Dictionary  " << name << " not found." << std::endl;
  }

  void list()
  {
    std::cout << "Dictionaries:" << std::endl;
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      std::cout << it->first << std::endl;
    }
  }

  void unite(const std::string& newName, const std::string& name1, const std::string& name2)
  {
    Dictionary dict1, dict2;

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name1)
      {
        dict1 = it->second;
        break;
      }
    }

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name2)
      {
        dict2 = it->second;
        break;
      }
    }

    Dictionary newDict;
    for (auto entryIt = dict1.begin(); entryIt != dict1.end(); ++entryIt)
    {
      newDict.push_back(*entryIt);
    }
    for (auto entryIt = dict2.begin(); entryIt != dict2.end(); ++entryIt)
    {
      bool exists = false;
      for (auto newEntryIt = newDict.begin(); newEntryIt != newDict.end(); ++newEntryIt)
      {
        if (newEntryIt->first == entryIt->first)
        {
          exists = true;
          break;
        }
      }
      if (!exists)
      {
        newDict.push_back(*entryIt);
      }
    }

    dictionaries.push_back({ newName, newDict });
    std::cout << "Dictionaries \"" << name1 << "\" and \""
      << name2 << "\" united into \"" << newName << "\"." << std::endl;
  }

  void add(const std::string& name1, const std::string& name2)
  {
    Dictionary dict1, dict2;

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name1)
      {
        dict1 = it->second;
        break;
      }
    }

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name2)
      {
        dict2 = it->second;
        break;
      }
    }

    for (auto entryIt = dict2.begin(); entryIt != dict2.end(); ++entryIt)
    {
      bool exists = false;
      for (auto existingIt = dict1.begin(); existingIt != dict1.end(); ++existingIt)
      {
        if (existingIt->first == entryIt->first)
        {
          exists = true;
          break;
        }
      }
      if (!exists)
      {
        dict1.push_back(*entryIt);
      }
    }

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name1)
      {
        it->second = dict1;
        std::cout << "Added entries from \""
          << name2 << "\" to \"" << name1 << "\"." << std::endl;
        return;
      }
    }
  }

  void intersection(const std::string& newName,
    const std::string& name1, const std::string& name2)
  {
    Dictionary dict1, dict2;

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name1)
      {
        dict1 = it->second;
        break;
      }
    }

    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name2)
      {
        dict2 = it->second;
        break;
      }
    }

    Dictionary newDict;
    for (auto entryIt1 = dict1.begin(); entryIt1 != dict1.end(); ++entryIt1)
    {
      for (auto entryIt2 = dict2.begin(); entryIt2 != dict2.end(); ++entryIt2)
      {
        if (entryIt1->first == entryIt2->first)
        {
          newDict.push_back(*entryIt1);
          break;
        }
      }
    }

    dictionaries.push_back({ newName, newDict });
    std::cout << "Dictionary " << newName
      << " created by intersecting " << name1 << " and " << name2 << '\n';
  }

  void insert(const std::string& name, const std::string& key, const std::string& translation)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        it->second.push_back({ key, translation });
        std::cout << "Element " << key << " added to dictionary " << name << '\n';
        return;
      }
    }
    std::cout << "No dictionary with this name exists\n";
  }

  void find(const std::string& name, const std::string& key)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        for (auto entryIt = it->second.begin(); entryIt != it->second.end(); ++entryIt)
        {
          if (entryIt->first == key)
          {
            std::cout << "Found: " << key << " -> " << entryIt->second << std::endl;
            return;
          }
        }
        std::cout << "Key \"" << key << "\" not found in dictionary \"" << name << "\"." << std::endl;
        return;
      }
    }
    std::cout << "Dictionary \"" << name << "\" not found." << std::endl;
  }

  void change(const std::string& name, const std::string& key, const std::string& translation)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        for (auto entryIt = it->second.begin(); entryIt != it->second.end(); ++entryIt)
        {
          if (entryIt->first == key)
          {
            entryIt->second = translation;
            std::cout << "Changed: " << key << " -> " << translation << std::endl;
            return;
          }
        }
        std::cout << "Key \"" << key << "\" not found in dictionary \"" << name << "\"." << std::endl;
        return;
      }
    }
    std::cout << "Dictionary \"" << name << "\" not found." << std::endl;
  }

  void findLetter(const std::string& name, char letter)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        std::cout << "Entries starting with '" << letter << "' in dictionary \"" << name << "\":" << std::endl;
        for (auto entryIt = it->second.begin(); entryIt != it->second.end(); ++entryIt)
        {
          if (entryIt->first[0] == letter)
          {
            std::cout << entryIt->first << ": " << entryIt->second << std::endl;
          }
        }
        return;
      }
    }
    std::cout << "Dictionary \"" << name << "\" not found." << std::endl;
  }

  void deleteElem(const std::string& name, const std::string& key)
  {
    for (auto it = dictionaries.begin(); it != dictionaries.end(); ++it)
    {
      if (it->first == name)
      {
        for (auto entryIt = it->second.begin(); entryIt != it->second.end(); ++entryIt)
        {
          if (entryIt->first == key)
          {
            it->second.erase(entryIt);
            std::cout << "Deleted: " << key << " from dictionary \"" << name << "\"." << std::endl;
            return;
          }
        }
        std::cout << "Key \"" << key << "\" not found in dictionary \"" << name << "\"." << std::endl;
        return;
      }
    }
    std::cout << "Dictionary \"" << name << "\" not found." << std::endl;
  }
}
