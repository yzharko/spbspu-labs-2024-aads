#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char* argv[])
{
  using namespace jirkov;
  Queue< std::string > someQueue;
  Stack< long long > someStack;

  if (argc == 1)
  {
    //input function
  }
  else if (argc == 2)
  {
    // input something
  }
  else
  {
    std::cerr << "Wrong input" << "\n";
    return 1;
  }
  try
  {
    //functions
  }
  catch (std::exception &e)
  {
    std::cout << e.what();
    return 1;
  }
  return 0;
}
