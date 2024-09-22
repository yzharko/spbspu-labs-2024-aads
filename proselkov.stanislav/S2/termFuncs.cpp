#include "termFuncs.hpp"
#include <limits>
#include <math.h>

bool proselkov::checkOperand(std::string symb)
{
  for (char c : symb)
  {
    if (std::isdigit(c))
    {
      return true;
    }
  }
  return false;
}

bool proselkov::checkOperator(std::string symb)
{
  if (symb == "*" || symb == "/" || symb == "%" || symb == "+" || symb == "-")
  {
    return true;
  }
  return false;
}

int proselkov::priori(std::string symb)
{
  if (symb == "+" || symb == "-")
  {
    return 1;
  }
  else if (symb == "*" || symb == "/" || symb == "%")
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

void proselkov::readTerms(std::istream& in, Queue< std::string >& terms)
{
  std::string term;
  while (!in.eof())
  {
    std::getline(in, term);
    if (!term.empty())
    {
      terms.push(term);
    }
  }
}

void proselkov::makeQueue(std::string strTerm, Queue< std::string >& queue)
{
  size_t termLen = 0;
  std::string symb = "";
  while (termLen < strTerm.length())
  {
    if (strTerm[termLen] == ' ')
    {
      termLen++;
      queue.push(symb);
      symb = "";
    }
    else if (termLen == (strTerm.length() - 1))
    {
      symb += strTerm[termLen];
      queue.push(symb);
      termLen++;
    }
    else
    {
      symb += strTerm[termLen];
      termLen++;
    }
  }
}

void proselkov::postfixation(Queue< std::string >& infix, Queue< std::string >& postfix)
{
  Stack< std::string > interDepot;
  while (!infix.isEmpty())
  {
    std::string elem = infix.getFront();
    infix.pop();
    if (checkOperand(elem))
    {
      postfix.push(elem);
    }
    else if (elem == "(")
    {
      interDepot.push("(");
    }
    else if (elem == ")")
    {
      while (interDepot.getTop() != "(")
      {
        postfix.push(interDepot.getTop());
        interDepot.pop();
      }
      interDepot.pop();
    }
    else
    {
      while ((!interDepot.isEmpty() && priori(elem) < priori(interDepot.getTop())) ||
        (!interDepot.isEmpty() && priori(elem) == priori(interDepot.getTop())))
      {
        postfix.push(interDepot.getTop());
        interDepot.pop();
      }
      interDepot.push(elem);
    }
  }
  while (!interDepot.isEmpty())
  {
    postfix.push(interDepot.getTop());
    interDepot.pop();
  }
}

long long proselkov::makeOperation(long long first, long long second, std::string operation)
{
  long long res = 0;
  if (operation == "+")
  {
    if (((first > 0 && second > 0)) && (first > (std::numeric_limits< long long >::max() - second)))
    {
      throw std::overflow_error("Error: Value overflow!");
    }
    if ((first < 0 && second < 0) && (first < (std::numeric_limits< long long >::min() + abs(second))))
    {
      throw std::overflow_error("Error: Value overflow!");
    }
    res = first + second;
  }
  else if (operation == "-")
  {
    if ((first > 0 && second < 0))
    {
      if ((abs(second) > (std::numeric_limits< long long >::max() - first)))
      {
        throw std::overflow_error("Error: Value overflow!");
      }
      if (second == std::numeric_limits< long long >::min())
      {
        throw std::overflow_error("Error: Value overflow!");
      }
    }
    if ((first < 0 && second > 0) && (second > (abs(std::numeric_limits< long long >::min() - first))))
    {
      throw std::overflow_error("Error: Value overflow!");
    }
    res = first - second;
  }
  else if (operation == "/")
  {
    res = first / second;
  }
  else if (operation == "*")
  {
    if ((first > 0 && second > 0))
    {
      if (((std::numeric_limits< long long >::max() / abs(first)) < abs(second)))
      {
        throw std::overflow_error("Error: Value overflow!");
      }
    }
    if ((first < 0 && second < 0) || (first > 0 && second < 0))
    {
      if (((std::numeric_limits< long long >::min() / abs(first)) > second))
      {
        throw std::overflow_error("Error: Value overflow!");
      }
    }
    if ((first < 0 && second > 0))
    {
      if (((std::numeric_limits< long long >::min() / second) > first))
      {
        throw std::overflow_error("Error: Value overflow!");
      }
    }
    res = first * second;
  }
  else if (operation == "%")
  {
    res = first < 0 ? (first % second + second) : first % second;
  }
  else
  {
    res = 0;
  }

  return res;
}

long long proselkov::calculateTerm(Queue< std::string >& term)
{
  Stack< long long > stack;

  long long first;
  long long second;

  std::string symb;
  while (!term.isEmpty())
  {
    symb = term.getFront();
    term.pop();
    if (checkOperand(symb))
    {
      stack.push(std::stoll(symb));
    }
    else if (checkOperator(symb))
    {
      second = stack.getTop();
      stack.pop();
      first = stack.getTop();
      stack.pop();
      stack.push(makeOperation(first, second, symb));
    }
    else
    {
      throw std::logic_error("Error: Term is incorrect!\n");
    }
  }
  unsigned long long result = stack.getTop();
  stack.pop();
  return result;
}

void proselkov::makeResults(Queue< std::string >& terms, Stack< long long >& results)
{
  std::string strTerm;
  long long res = 0;

  Queue< std::string > infix;
  Queue< std::string > postfix;

  while (!terms.isEmpty())
  {
    strTerm = terms.getFront();
    terms.pop();
    makeQueue(strTerm, infix);
    postfixation(infix, postfix);

    res = calculateTerm(postfix);
    results.push(res);
  }
}
