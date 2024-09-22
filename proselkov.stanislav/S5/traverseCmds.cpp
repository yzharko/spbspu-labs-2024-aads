#include "traverseCmds.hpp"
#include "taskSumm.hpp"

std::ostream& proselkov::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& proselkov::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
  return out;
}

using base_t = proselkov::avlTree< long long, std::string >;

void proselkov::fillTree(std::istream& in, base_t& data)
{
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
    }

    long long key;
    std::string value;

    if (in >> key >> value)
    {
      data.insert({ key, value });
    }
  }
}

void proselkov::ascending(std::ostream& out, base_t& data)
{
  proselkov::TaskSumm summ;
  summ = data.traverseLnR< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}

void proselkov::descending(std::ostream& out, base_t& data)
{
  proselkov::TaskSumm summ;
  summ = data.traverseRnL< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}

void proselkov::breadth(std::ostream& out, base_t& data)
{
  proselkov::TaskSumm summ;
  summ = data.traverseBre< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}
