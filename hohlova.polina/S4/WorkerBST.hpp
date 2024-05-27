#ifndef WORKERBST_HPP
#define WORKERBST_HPP
#include "BinarySearchTree.hpp"

class WorkerBST {
    BinarySearchTree<std::string, BinarySearchTree<int, std::string>* > bst;

public:
    WorkerBST(const std::string& path);
    ~WorkerBST();
    void Menu();
private:
    void ReadFile(const std::string& path);

    void Print(const std::string&, size_t& pos);

    void Complement(const std::string&, size_t& pos);

    void Intersect(const std::string&, size_t& pos);

    void Union(const std::string&, size_t& pos);

    void ParseArguments(const std::string& str);

    int ParseNum(const std::string& num);
    void ReadDataSet(const std::string& dataSet);

};


#endif
