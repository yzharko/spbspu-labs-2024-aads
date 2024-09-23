#include "commands.hpp"
#include "KeyValSumm.hpp"

void popov::strToTree(std::string expression, BST< int, std::string >& dict)
{
  std::string symbol = "";
  size_t i = 0;
  size_t count = 0;
  std::string name;
  int key;
  std::string value;
  while (i < expression.length())
  {
    if (expression[i] == ' ')
    {
      i++;
      count++;
      if (count % 2 != 0)
      {
        key = std::stoi(symbol);
      }
      else
      {
        value = symbol;
        dict.insert(key, value);
      }
      symbol = "";
    }
    else if (i == (expression.length() - 1))
    {
      symbol += expression[i];
      i++;
      if (count == 0)
      {
        name = symbol;
      }
      else
      {
        value = symbol;
        dict.insert(key, value);
      }
      return;
    }
    else
    {
      symbol += expression[i];
      i++;
    }
  }
}

void popov::ascending(std::ostream& out, const BST< int, std::string >& tree)
{
  KeyValSumm result;
  result = tree.traverse_lnr< KeyValSumm >(result);
  out << result.keySum_ << " " << result.valSum_ << "\n";
}

void popov::descending(std::ostream& out, const BST< int, std::string >& tree)
{
  KeyValSumm result;
  result = tree.traverse_rnl< KeyValSumm >(result);
  out << result.keySum_ << " " << result.valSum_ << "\n";
}

void popov::breadth(std::ostream& out, const BST< int, std::string >& tree)
{
  KeyValSumm result;
  result = tree.traverse_breadth< KeyValSumm >(result);
  out << result.keySum_ << " " << result.valSum_ << "\n";
}

void popov::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}

void popov::outInvCom(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

void popov::outRange(std::ostream& out)
{
  out << "<OUT OF RANGE>\n";
}
