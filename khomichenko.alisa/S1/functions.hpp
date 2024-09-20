#ifndef FUNC_HPP
#define FUNC_HPP
#include <string>
#include <iostream>
#include <utility>
#include <limits>
#include <cctype>
#include "list.hpp"

namespace khomichenko
{
    using mainList = List <std::pair <std::string, List<unsigned long long>>>;

    mainList listInput(std::istream& input)
    {
        mainList lstt;
        std::string newwords;
        const unsigned long long maximum = std::numeric_limits<unsigned long long>::max();
        while (input >> newwords)
        {
            if (std::isalpha(newwords[0]))
            {
                lstt.pushBack({ newwords, List <unsigned long long>() });
            }
            else if (std::stoull(newwords) <= maximum)
            {
                lstt.end()->second.pushBack(std::stoull(newwords));
            }
            else
            {
                std::overflow_error("overflow error");
            }
        }
        return lstt;
    }

    void namesOut(mainList list)
    {
        mainList::Iterator iter = list.begin();
        while (iter != list.end())
        {
            std::cout << iter->first << " ";
            iter++;
        }
        std::cout << iter->first << "\n";
    }

    List <List <unsigned long long>> remadeLists(mainList hugeList)
    {
         List <List <unsigned long long>> lists;
         List<unsigned long long>::Iterator iter;
         List <List <unsigned long long>>::Iterator listsIter;
         lists.pushBack(List <unsigned long long>());
         while (!hugeList.empty())
         {
             iter = hugeList.begin()->second.begin();
             listsIter = lists.begin();
             while (!hugeList.begin()->second.empty())
             {
                 if (iter != hugeList.begin()->second.end() && listsIter == lists.end()) 
                 {
                     lists.pushBack(List <unsigned long long>());
                 }
                 listsIter->pushBack(*iter);
                 iter++;
                 listsIter++;
                 hugeList.begin()->second.popFront();
             }
             hugeList.popFront();
         }
         return lists;
    }

    List <unsigned long long> getSums(List <List <unsigned long long>> lists)
    {
        List <unsigned long long>::Iterator iter;
        List <List <unsigned long long>>::Iterator hugeIter;
        List <unsigned long long> sums;
        unsigned long long sum;
        hugeIter = lists.begin();
        while (hugeIter != lists.end())
        {
            iter = hugeIter->begin();
            sum = 0;
            while (iter != hugeIter->end())
            {
                sum = sum + *iter;
                iter++;
            }
            sum = sum + *iter;
            hugeIter++;
            sums.pushBack(sum);
        }
        iter = hugeIter->begin();
        sum = 0;
        while (iter != hugeIter->end())
        {
            sum = sum + *iter;
            iter++;

        }
        sum = sum + *iter;
        hugeIter++;
        sums.pushBack(sum);
        return sums;
    }
}
#endif
