#include <string>
#include <iostream>
#include <utility>
#include <cctype>
#include "functions.hpp"
#include "list.hpp"

using mainList = List <std::pair <std::string, List<unsigned long long>>>;
int main()
{
    using namespace khomichenko;
    mainList lst;
    List<int> list;
    List <List<unsigned long long>> lists;
    lst = listInput(std::cin);
    namesOut(lst);
    lists = remadeLists(lst);
    List<List<unsigned long long>>::Iterator iter = lists.begin();
    List <unsigned long long> sums = getSums(lists);
    while (!lists.empty())
    {
        iter->print();
        iter++;
        lists.popFront();
    }
    sums.print();
}
