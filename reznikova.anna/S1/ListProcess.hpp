#ifndef LIST_PROCESS_HPP
#define LIST_PROCESS_HPP
#include "List.hpp"

namespace reznikova

{
void inputList(std::istream & input, List< std::pair< std::string, List< size_t > > > & list);
size_t findMaxLenOfArgs(List< std::pair < std::string, List< size_t > > > & list);
List< size_t > countSums(List< std::pair< std::string, List< size_t > > > & list);
void outputNames(std::ostream & output, List< std::pair < std::string, List< size_t > > > & list);
void outputArgs(std::ostream & output, List< std::pair< std::string, List< size_t > > > & list);
void outputSums(std::ostream & output, List< size_t > & sums);
}

#endif
