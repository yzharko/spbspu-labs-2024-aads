#include <iostream>
#include <fstream>
#include "BinarySearchTree.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include "WorkerBST.hpp"

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
        std::cout << err.what();
        return 1;
    }
    return 0;
}
