#include "command.hpp"

void zasulsky::print(Dictionary < std::string, Dictionary < int, std::string > >& dicBig, std::string name, std::ostream& out)
{
  if (name == "")
  {
    throw std::runtime_error("not enough argument");
  }
  ConstBidIter <std::string, Dictionary<int, std::string> > it = dicBig.lookfor(name);
  if (dicBig.isEmptyIt(it))
  {
    out << "<INVALID COMMAND>\n";
  }
  else if (!(dicBig.lookfor(name)->second.isEmpty()))
  {
    out << name;
    dicBig.lookfor(name)->second.print();
  }
  else
  {
    out << "<EMPTY>\n";
  }
}


void zasulsky::intersect(Dictionary < std::string, Dictionary < int, std::string >>& dicBig, std::string p1, std::string p2, std::string res)
{
  if (!(res != "" && p1 != "" && p2 != ""))
  {
    throw std::runtime_error("not enough arguments");
  }
  ConstBidIter <std::string, Dictionary<int, std::string> > it = dicBig.lookfor(p1);
  ConstBidIter <std::string, Dictionary<int, std::string> > it2 = dicBig.lookfor(p2);
  if (!dicBig.isEmptyIt(it) && !dicBig.isEmptyIt(it2))
  {
    Dictionary <int, std::string> lhs = dicBig.lookfor(p1)->second;
    Dictionary <int, std::string> rhs = dicBig.lookfor(p2)->second;
    auto nD = lhs.cross(rhs);
    if (p1 == res)
    {
      dicBig.lookfor(p1)->second.clear();
      dicBig.lookfor(p1)->second = nD;
      dicBig.lookfor(p1)->second.sort();
    }
    else if (p2 == res)
    {
      dicBig.lookfor(p2)->second.clear();
      dicBig.lookfor(p2)->second = nD;
      dicBig.lookfor(p2)->second.sort();
    }
    else
    {
      auto it = dicBig.lookfor(res);
      if (dicBig.isEmptyIt(it))
      {
        dicBig.insert(make_pair(res, nD));
      }
      else
      {
        it->second.clear();
        it->second = nD;
      }
    }
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}


void zasulsky::complement(Dictionary < std::string, Dictionary < int, std::string> >& dicBig, std::string p1, std::string p2, std::string res)
{
  if (!(res != "" && p1 != "" && p2 != ""))
  {
    throw std::runtime_error("not enough arguments");
  }
  ConstBidIter <std::string, Dictionary<int, std::string> > it = dicBig.lookfor(p1);
  ConstBidIter <std::string, Dictionary<int, std::string> > it2 = dicBig.lookfor(p2);
  if (!dicBig.isEmptyIt(it) && !dicBig.isEmptyIt(it2))
  {
    Dictionary <int, std::string> lhs = dicBig.lookfor(p1)->second;
    Dictionary <int, std::string> rhs = dicBig.lookfor(p2)->second;
    auto nD = lhs.subtract(rhs);
    if (p1 == res)
    {
      dicBig.lookfor(p1)->second.clear();
      dicBig.lookfor(p1)->second = nD;
      dicBig.lookfor(p1)->second.sort();
    }
    else if (p2 == res)
    {
      dicBig.lookfor(p2)->second.clear();
      dicBig.lookfor(p2)->second = nD;
      dicBig.lookfor(p2)->second.sort();
    }
    else
    {
      auto it = dicBig.lookfor(res);
      if (dicBig.isEmptyIt(it))
      {
        dicBig.insert(make_pair(res, nD));
      }
      else
      {
        it->second.clear();
        it->second = nD;
      }
    }
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}


void zasulsky::getUnion(Dictionary < std::string, Dictionary < int, std::string > >& dicBig, std::string p1, std::string p2, std::string res)
{
  if (!(res != "" && p1 != "" && p2 != ""))
  {
    throw std::runtime_error("not enough arguments");
  }
  auto it = dicBig.lookfor(p1);
  auto  it2 = dicBig.lookfor(p2);
  if (!dicBig.isEmptyIt(it) && !dicBig.isEmptyIt(it2))
  {
    Dictionary <int, std::string> lhs = dicBig.lookfor(p1)->second;
    Dictionary <int, std::string> rhs = dicBig.lookfor(p2)->second;
    auto nD = lhs.merge(rhs);
    if (p1 == res)
    {
      dicBig.lookfor(p1)->second.clear();
      dicBig.lookfor(p1)->second = nD;
      dicBig.lookfor(p1)->second.sort();
    }
    else if (p2 == res)
    {
      dicBig.lookfor(p2)->second.clear();
      dicBig.lookfor(p2)->second = nD;
      dicBig.lookfor(p2)->second.sort();
    }
    else
    {
      auto it = dicBig.lookfor(res);
      if (dicBig.isEmptyIt(it))
      {
        dicBig.insert(make_pair(res, nD));
      }
      else
      {
        it->second.clear();
        it->second = nD;
      }
    }
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

std::ostream& zasulsky::printInvCmd(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
}

void zasulsky::skipUntilNewLine(std::istream& in)
{
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  in.ignore(maxstream, '\n');
}

bool zasulsky::isOperand(std::string st)
{
  for (char s : st)
  {
    if (!isdigit(s))
    {
      return false;
    }
  }
  return true;
}
