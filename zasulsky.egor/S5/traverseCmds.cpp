#include "traverseCmds.hpp"
#include "taskSumm.hpp"

std::ostream& zasulsky::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& zasulsky::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
  return out;
}

using base_t = zasulsky::avlTree< long long, std::string >;

void zasulsky::fillTree(std::istream& in, base_t& data)
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

void zasulsky::ascending(std::ostream& out, base_t& data)
{
  zasulsky::TaskSumm summ;
  summ = data.traverseLnR< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}

void zasulsky::descending(std::ostream& out, base_t& data)
{
  zasulsky::TaskSumm summ;
  summ = data.traverseRnL< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}

void zasulsky::breadth(std::ostream& out, base_t& data)
{
  zasulsky::TaskSumm summ;
  summ = data.traverseBre< TaskSumm >(summ);

  out << summ.getKeySumm() << summ.getValSumm() << "\n";
}
