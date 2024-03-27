#include "list.hpp"
#include <limits>

int main()
{
  hohlova::List<std::pair<std::string, std::vector<unsigned long long>>> numbers;
  hohlova::List<unsigned long long> sums;
  std::string line;
  bool hasData = false;
  std::string temp;
  bool err = false;

  while (std::getline(std::cin, line) && !line.empty())
  {
    std::istringstream iss(line);
    std::string word;
    iss >> word;
    temp = word;

    std::vector<unsigned long long> nums;

    std::string numStr;
    while (iss >> numStr)
    {
      nums.push_back(std::stoull(numStr));
    }

    numbers.push_back(std::make_pair(word, nums));

    if (!nums.empty())
      hasData = true;
  }

  if (numbers.size() == 0)
  {
    std::cout << 0 << '\n';
  }
  else
  {
    if (!hasData)
    {
      std::cout << temp << "\n" << 0 << "\n";
      return 0;
    }
    size_t max_length = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
      max_length = std::max(max_length, (*it).second.size());
    }

    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
      std::cout << (*it).first;
      auto nextIt = it;
      ++nextIt;
      if (nextIt != numbers.end())
      {
        std::cout << " ";
      }
    }
    std::cout << std::endl;

    size_t max_size = 0;
    for (const auto& pair : numbers)
    {
      const auto& sequence = pair.second;
      max_size = std::max(max_size, sequence.size());
    }

    for (size_t i = 0; i < max_size; ++i)
    {
      bool firstElement = true;
      for (const auto& pair : numbers)
      {
        const auto& sequence = pair.second;
        if (i < sequence.size())
        {
          if (!firstElement)
          {
            std::cout << " ";
          }
          std::cout << sequence[i];
          firstElement = false;
        }
      }
      std::cout << std::endl;
    }

    try
    {
      for (size_t i = 0; i < max_length; ++i)
      {
        unsigned long long sum = 0;
        for (auto it = numbers.begin(); it != numbers.end(); ++it)
        {
          if (i < (*it).second.size())
          {
            if (sum > std::numeric_limits<unsigned long long>::max() - (*it).second[i])
            {
              throw std::overflow_error("Overflow");
            }
            sum += (*it).second[i];
          }
        }
        sums.push_back(sum);
      }
    }
    catch (const std::overflow_error& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
    for (auto it = sums.begin(); it != sums.end(); ++it)
    {
      std::cout << (*it);
      auto nextIt = it;
      ++nextIt;
      if (nextIt != sums.end())
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  if (err)
    return 1;
  return 0;
}
