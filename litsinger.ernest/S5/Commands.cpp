#include "Commands.hpp"
#include "TreeProcessing.hpp"
#include "TraverseObject.hpp"

void litsinger::ascendingCommand(Tree< int, std::string > & tree)
{
  if (tree.isEmpty())
  {
    outputEmptyError(std::cout);
    return;
  }
  Traverse operation;
  try
  {
    Traverse result = tree.traverse_lnr(operation);
    output(result);
  }
  catch (std::exception & e)
  {
    throw std::runtime_error(e.what());
  }
}

void litsinger::descendingCommand(Tree< int, std::string > & tree)
{
  if (tree.isEmpty())
  {
    outputEmptyError(std::cout);
    return;
  }
  Traverse operation;
  try
  {
    Traverse result = tree.traverse_rnl(operation);
    output(result);
  }
  catch (std::exception & e)
  {
    throw std::runtime_error(e.what());
  }
}

void litsinger::breadthCommand(Tree< int, std::string > & tree)
{
  if (tree.isEmpty())
  {
    outputEmptyError(std::cout);
    return;
  }
  Traverse operation;
  try
  {
    Traverse result = tree.traverse_breadth(operation);
    output(result);
  }
  catch (std::exception & e)
  {
    throw std::runtime_error(e.what());
  }
}

