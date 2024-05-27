#include "WorkerBST.hpp"
#include <fstream>
#include <vector>
#include <string>
WorkerBST::WorkerBST(const std::string& path) {
    ReadFile(path);
}

WorkerBST::~WorkerBST() {
    auto it = bst.begin();

    while (it != bst.end())
    {
        auto ptr = (*it).second;
        delete  ptr;
        ++it;
    }
}

void WorkerBST::Menu() {

    std::string line;

    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        if (!line.empty()) {
            ParseArguments(line);
        }
    }
}
void WorkerBST::ReadFile(const std::string& path) {

    if (path.empty())
        std::runtime_error("Path is empty");

    std::ifstream file(path);

    if (!file.is_open())
        std::runtime_error("File not open");


    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        ReadDataSet(line);
    }
}

void WorkerBST::Print(const std::string& str, size_t& pos)
{
    std::string word;
    BinarySearchTree<int, std::string>* findBst = nullptr;
    while (pos <= str.size()) {
        if (pos == str.size() || str[pos] == ' ') {
            findBst = bst.get(word);
            //print word = "";
            break;
        }
        else {
            word += str[pos];
            ++pos;
        }
    }

    if (findBst == nullptr || findBst->empty())
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    auto it = findBst->begin();
    std::cout << word << ' ';
    while (it != findBst->end())
    {
        std::cout << (*it).first << ' ' << (*it).second << ' ';
        ++it;
    }
    std::cout << std::endl;
}

void WorkerBST::Complement(const std::string& str, size_t& pos)
{
    std::string word;
    BinarySearchTree<int, std::string>* first = nullptr;
    BinarySearchTree<int, std::string>* second = nullptr;
    BinarySearchTree<int, std::string>* result = nullptr;

    while (pos <= str.size()) {
        if (str[pos] == ' ' || pos == str.size()) {
            if (!result)
            {
                result = new BinarySearchTree<int, std::string>;
                bst.push(std::move(word), result);

            }
            else if (!first)
                first = bst.get(std::move(word));
            else if (!second)
                second = bst.get(std::move(word));

            word = "";
        }
        else {
            word += str[pos];
        }
        ++pos;
    }

    if (!second || !first || !result)
        throw std::runtime_error("Ivalid Argument");

    auto itF = first->begin();


    while (itF != first->end())
    {
        auto res = second->contains((*itF).first);
        if (!res)
        {
            result->push((*itF).first, (*itF).second);
        }
        ++itF;
    }

}

int WorkerBST::ParseNum(const std::string& num) {

    size_t pos = 0;
    auto symbol = static_cast<unsigned char>(num[pos]);
    long long result = 0;
    while (std::isdigit(symbol)) {
        result = result * 10 + (symbol - '0');

        if (pos == num.size() - 1) {
            pos++;
            break;
        }

        symbol = static_cast<unsigned char>(num[++pos]);
    }
    return result;

}

void WorkerBST::ReadDataSet(const std::string& dataSet) {

    size_t pos = 0;
    std::string word;
    word.reserve(10);
    std::vector<std::string> stringList;
    stringList.reserve(10);

    while (pos <= dataSet.size()) {
        if (std::isspace(dataSet[pos]) || pos == dataSet.size()) {
            stringList.push_back(word);
            word = "";
        }
        else {
            word += dataSet[pos];
        }
        ++pos;
    }

    size_t i = 1;



    BinarySearchTree<int, std::string>* newTree = new BinarySearchTree<int, std::string>;
    bst.push(stringList[0], newTree);

    while (i < stringList.size() - 1)
    {
        newTree->push(ParseNum(stringList[i]), stringList[i + 1]);
        i += 2;
    }

}



void WorkerBST::Intersect(const std::string& str, size_t& pos)
{

    std::string word;
    BinarySearchTree<int, std::string>* first = nullptr;
    BinarySearchTree<int, std::string>* second = nullptr;
    BinarySearchTree<int, std::string>* result = nullptr;
    while (pos <= str.size()) {
        if (str[pos] == ' ' || pos == str.size()) {
            if (!result)
            {
                result = new BinarySearchTree<int, std::string>;
                bst.push(std::move(word), result);

            }
            else if (!first)
                first = bst.get(std::move(word));
            else if (!second)
                second = bst.get(std::move(word));

            word = "";
        }
        else {
            word += str[pos];
        }
        ++pos;
    }


    if (!second || !first || !result)
        throw std::runtime_error("Ivalid Argument");

    auto itF = first->begin();

    while (itF != first->end())
    {
        auto res = second->contains((*itF).first);
        if (res)
        {
            result->push((*itF).first, (*itF).second);
        }
        ++itF;
    }

}

void WorkerBST::Union(const std::string& str, size_t& pos)
{
    std::string word;
    BinarySearchTree<int, std::string>* first = nullptr;
    BinarySearchTree<int, std::string>* second = nullptr;
    BinarySearchTree<int, std::string>* result = nullptr;
    while (pos <= str.size()) {
        if (str[pos] == ' ' || pos == str.size()) {
            if (!result)
            {
                result = new BinarySearchTree<int, std::string>;
                bst.push(std::move(word), result);

            }
            else if (!first)
                first = bst.get(std::move(word));
            else if (!second)
                second = bst.get(std::move(word));

            word = "";
        }
        else {
            word += str[pos];
        }
        ++pos;
    }

    if (!second || !first || !result)
        throw std::runtime_error("Ivalid Argument");

    auto itF = first->begin();
    auto itS = second->begin();

    while (itF != first->end() || itS != second->end())
    {
        if (itF != first->end())
        {
            if (!result->contains((*itF).first))
            {
                result->push((*itF).first, (*itF).second);
            }
            ++itF;
        }

        if (itS != second->end())
        {
            if (!result->contains((*itS).first))
            {
                result->push((*itS).first, (*itS).second);
            }
            ++itS;
        }


    }
}

void WorkerBST::ParseArguments(const std::string& str/*, BinarySearchTree<int, std::string> bst*/) {

    std::string word;

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            if (word == "print") {
                Print(str, ++i);
            }
            else if (word == "intersect") {
                Intersect(str, ++i);
            }
            else if (word == "complement") {
                Complement(str, ++i);
            }
            else if (word == "union") {
                Union(str, ++i);
            }
            else {
                std::cout << "IVALID COMMAND" << std::endl;
            }
            word = "";
        }
        else {
            word += str[i];
        }
    }

}
