#include "TreeProcessing.hpp"
#include <iostream>
#include <string>

void litsinger::outputInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void litsinger::outputEmptyError(std::ostream & out)
{
  out << "<EMPTY>\n";
}

std::string litsinger::getValue(std::string & input, size_t & i)
{
  std::string result = "";
  while (i < input.length() and input[i] != ' ')
  {
    result += input[i];
    i++;
  }
  i++;
  return result;
}

int litsinger::getKey(std::string & input, size_t & i)
{
  std::string result = "";
  while (i < input.length() and input[i] != ' ' and (isdigit(input[i]) or input[i] == '-'))
  {
    result += input[i];
    i++;
  }
  i++;
  return std::stoi(result);
}

void litsinger::readFromFile(std::istream & is, Tree< int, std::string > & tree)
{
  std::string input;
  getline(is, input);
  size_t i = 0;
  while (i < input.length())
  {
    int key = getKey(input, i);
    std::string value = getValue(input, i);
    tree.insert(key, value);
  }
}

void litsinger::output(Traverse & functor)
{
  std::cout << functor.result << " ";
  while (!functor.values.empty())
  {
    std::cout << functor.values.getValue();
    std::cout << ((functor.values.getSize() == 1) ? "\n" : " ");
    functor.values.pop();
  }
}

