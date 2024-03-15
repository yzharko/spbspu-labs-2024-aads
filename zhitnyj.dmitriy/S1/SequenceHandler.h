#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

#include "List.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class SequenceHandler
{
private:
    List<std::string> names;
    List<List<unsigned long long>> sequences;

public:
    SequenceHandler() = default;

    void addSequence(const std::string& name, const List<unsigned long long>& sequence);
    void printSequences();
    void rearrangeAndPrint();
};

#endif
