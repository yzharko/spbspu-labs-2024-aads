#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< int > > > seqsPair;
  Funcs< int > func;
  try
  {
    func.input_(std::cin, seqsPair);
    func.outputName_(seqsPair);
    func.outputSeqs_(seqsPair);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
