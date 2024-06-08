#include "printErrors.hpp"

void hohlova::printEmpty(std::ostream& output)
{
    output << "<EMPTY>\n";
}

void hohlova::printInvCom(std::ostream& output)
{
    output << "<INVALID COMMAND>\n";
}
