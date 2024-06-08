#include <iostream>
#include <fstream>
#include "BinarySearchTree.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include "WorkerBST.hpp"
#include "printErrors.hpp"

int main(int argc, char** argv)
{
    std::ifstream input(argv[1]);
    if (argc < 1)
    {
        std::cerr << "Error! Empty list";
        return 1;
    }
    try
    {
        WorkerBST work(argv[1]);
        work.Menu();
    }
    catch (const std::exception& err)
    {
        hohlova::printInvCom(std::cout);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}
