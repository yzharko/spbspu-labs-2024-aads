#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  List< std::pair< std::string, List< unsigned long long > > > seqsPair;
  List< unsigned long long > listSumm;
  size_t maxSize = 0;
  try
  {
    input_(std::cin, seqsPair);
    outputName_(seqsPair, maxSize);
    outputSeqs_(seqsPair, listSumm, maxSize);
    outputSumm_(listSumm, maxSize);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 0;
  }
  return 0;
}
