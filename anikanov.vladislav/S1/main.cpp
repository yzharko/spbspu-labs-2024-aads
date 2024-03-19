#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "list.hpp"

anikanov::List< std::string > split(const std::string &str);

int main()
{
  using namespace anikanov;


  using list = List< unsigned long long >;
  using mainList = List< std::pair< std::string, list > >;

  std::unique_ptr< mainList > lists(new mainList );
  std::string inputName;
  std::string line;

  while (true) {
    line = "";
    std::getline(std::cin, line);
    if (std::cin.eof()) {
       break;
    }
    if (line == "") {
      continue;
    }
    List< std::string > inputList = split(line);
    list numbers;
    inputName = inputList.pop(0);
    for (auto &i : inputList) {
      numbers.push_back(std::stoull(i));
    }

    std::pair< std::string, List< unsigned long long > > list_pair;
    list_pair.first = inputName;
    list_pair.second = numbers;
    lists->push_back(list_pair);
  }


  for (auto it = lists->begin(); it != lists->end();) {
    std::cout << it->first;
    if (++it != lists->end()) {
      std::cout << " ";
    }
  }

  if (lists->empty()) {
    std::cout << "0\n";
    return 0;
  } else {
    std::cout << "\n";
  }

  bool finished = false;
  bool start_print = false;
  size_t idx = 0;
  List< unsigned long long > sums;
  bool bad_sum = false;

  while (!finished) {
    finished = true;
    start_print = true;
    for (auto list_it = lists->begin(); list_it != lists->end(); ++list_it) {
      const auto &list = *list_it;
      if (idx < list.second.size()) {
        if (finished) {
          sums.push_back(0);
          finished = false;
        }
        auto num_it = list.second.begin();
        for (size_t i = 0; i < idx; ++i) {
          num_it++;
        }
        if (start_print) {
          std::cout << *num_it;
          start_print = false;
        } else {
          std::cout << " " << *num_it;
        }
        if (*sums.back() + *num_it < std::max(*sums.back(), *num_it)) {
          std::cerr << "overflow\n";
          bad_sum = true;
        }
        *sums.back() += *num_it;
      }
    }
    std::cout << (finished ? "" : "\n");
    idx++;
  }

  if (bad_sum) {
    std::cerr << "overflow\n";
    return 1;
  }

  for (auto sum_it = sums.begin(); sum_it != sums.end();) {
    std::cout << *sum_it;
    if (++sum_it != sums.end()) {
      std::cout << " ";
    }
  }

  if (sums.empty()) {
    std::cout << "0";
  }

  std::cout << "\n";
  return 0;
}

anikanov::List< std::string > split(const std::string &str)
{
  anikanov::List< std::string > list;
  std::string cur = "";
  for (size_t pos = 0; pos != str.size(); ++pos) {
    if (str[pos] != ' ') {
      cur += str[pos];
    } else if (cur != "") {
      list.push_back(cur);
      cur = "";
    }
  }
  if (cur != "") {
    list.push_back(cur);
  }
  return list;
}
