#include "process.hpp"

bool khomichenko::isDigit(std::string str)
{
  size_t size = str.length();
  bool isNegative = false;
  if(str[0] == '-' && size > 1)
  {
    isNegative = true;
  }
  for(size_t i = 0; i < size; i++)
  {
    if(isNegative == true)
    {
      if(i > 0 && !std::isdigit(str[i]))
      {
        return false;
      }
    }
    else
    {
      if(!std::isdigit(str[i]))
      {
        return false;
      }
    }
  }
  return true;
}

void khomichenko::readData(std::istream& in, Tree< int, std::string >& tree)
{
  std::string dictionary = "";
  std::getline(in, dictionary);
  if(!dictionary.empty())
  {
    try
    {
      createTree(tree, dictionary);
    }
    catch(const std::exception& error)
    {
      throw;
    }
  }
}

void khomichenko::createTree(Tree< int, std::string >& tree, std::string dictionary)
{
  std::string temp = "";
  int key = 0;
  std::string value = "";
  for(size_t i = 0; i < dictionary.length(); i++)
  {
    if(dictionary[i] != ' ')
    {
      temp += dictionary[i];
    }
    else
    {
      if(isDigit(temp) == true)
      {
        try
        {
          key = std::stoi(temp);
        }
        catch(const std::out_of_range& error)
        {
          throw std::out_of_range("<VALUE IS OVERFLOW OR UNDERFLOW>");
        }
        temp = "";
      }
      else
      {
        value = temp;
        temp = "";
        tree.insert(key, value);
      }
    }
  }
  if(!value.empty())
  {
    value = temp;
    tree.insert(key, value);
  }
}

void khomichenko::getAscending(Tree< int, std::string >& tree)
{
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    TreeTraversal operation;
    TreeTraversal result = tree.traverse_lnr(operation);
    outTraversal(result);
  }
}

void khomichenko::getDescending(Tree< int, std::string >& tree)
{
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    TreeTraversal operation;
    TreeTraversal result = tree.traverse_rnl(operation);
    outTraversal(result);
  }
}

void khomichenko::getBreadth(Tree< int, std::string >& tree)
{
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    TreeTraversal operation;
    TreeTraversal result = tree.traverse_breadth(operation);
    outTraversal(result);
  }
}

void khomichenko::outTraversal(TreeTraversal& result)
{
  std::cout << result.result << " ";
  while(!result.allValue.isEmpty())
  {
    std::cout << result.allValue.front();
    result.allValue.pop();
    if(!result.allValue.isEmpty())
    {
      std::cout << " ";
    }
    else
    {
      std::cout << "\n";
    }
  }
}

void khomichenko::outText(std::ostream& out, std::string string)
{
  out << string << "\n";
}
