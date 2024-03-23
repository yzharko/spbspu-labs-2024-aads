#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "list.hpp"

int main() {
  Panov::List<std::pair<std::string, std::vector<int>>> sequences;

  std::string line;
  bool isEmpty = true;
  while (std::getline(std::cin, line)) {
    if (line.empty()) break;

    isEmpty = false;
    std::istringstream iss(line);
    std::string name;
    iss >> name;

    std::vector<int> sequence;
    int num;
    while (iss >> num)
      sequence.push_back(num);

    sequences.push_back({ name, sequence });
  }

  if (isEmpty) {
    std::cout << std::endl;
    return 0;
  }

  for (const auto& seq : sequences)
    std::cout << seq.first << ' ';
  std::cout << std::endl;

  size_t maxLength = 0;
  for (const auto& seq : sequences)
    maxLength = std::max(maxLength, seq.second.size());

  for (size_t i = 0; i < maxLength; ++i) {
    bool firstElement = true;
    for (const auto& seq : sequences) {
      if (i < seq.second.size()) {
        if (!firstElement)
          std::cout << ' ';
        else
          firstElement = false;
        std::cout << seq.second[i];
      }
    }
    std::cout << std::endl;
  }

  for (size_t i = 0; i < maxLength; ++i) {
    long long sum = 0;
    for (const auto& seq : sequences) {
      if (i < seq.second.size()) {
        if (static_cast<long long>(sum) + seq.second[i] > std::numeric_limits<int>::max()) {
          std::cerr << "Formed lists with exit code 1 and error message in standard error because of overflow" << std::endl;
          return 1;
        }
        sum += seq.second[i];
      }
    }
    std::cout << sum;
    if (i != maxLength - 1)
      std::cout << ' ';
  }
  std::cout << std::endl;

  return 0;
}
