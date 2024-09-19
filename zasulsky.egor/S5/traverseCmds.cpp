#include "traverseCmds.hpp"
#include "taskSumm.hpp"

std::ostream& zas::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& zas::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
  return out;
}

using base_t = zas::avlTree< long long, std::string >;

void zas::fillTree(std::istream& in, base_t& data)
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

void zas::ascending(std::ostream& out, base_t& data)
{
  zas::TaskSumm summ;
  summ = data.traverseLnR< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}

void zas::descending(std::ostream& out, base_t& data)
{
  zas::TaskSumm summ;
  summ = data.traverseRnL< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}

void zas::breadth(std::ostream& out, base_t& data)
{
  zas::TaskSumm summ;
  summ = data.traverseBre< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}
