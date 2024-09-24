#include <iostream>
#include <string>
#include "Iterator.hpp"
#include "List.hpp"
int main()
{
  using pair = std::pair<std::string, List<int>>;
  List<pair> pair_list;
  size_t max_length = 0;
  try
  {
    while (1)
    {
      std::string line;
      std::getline(std::cin, line);
      if (std::cin.eof())
        break;
      std::string str_name = "";
      std::string str_number = "";
      List<int> int_list;
      bool is_str_name = true;
      const size_t line_size = line.size();
      for (size_t i = 0; i <= line_size; i++)
      {
        if (i == line_size || line[i] == ' ')
        {
          if (is_str_name)
            is_str_name = false;
          else
          {
            int_list.push(std::stoi(str_number));
            max_length = (int_list.length() > max_length) ? int_list.length() : max_length;
            str_number = "";
          }
        }
        else
        {
          if (is_str_name)
            str_name += line[i];
          else
            str_number += line[i];
        }
      }
      pair_list.push({ str_name, int_list });
    }
    if (pair_list.empty())
    {
      pair_list.clear();
      return 0;
    }
    for (size_t i = 0; i < pair_list.length(); i++)
    {
      std::cout << pair_list[i].first << ((i + 1 == pair_list.length()) ? "" : " ");
    }
    std::cout << '\n';
    List<int> sum_list;
    for (size_t i = 0; i < max_length; i++)
    {
      size_t sum = 0;
      for (size_t j = 0; j < pair_list.length(); j++)
      {
        if (pair_list[j].second.length() > i)
        {
          sum += pair_list[j].second[i];
          std::cout << pair_list[j].second[i] << ((j + 1 == pair_list.length()) ? "" : " ");
        }
      }
      sum_list.push(sum);
      std::cout << '\n';
    }
    for (size_t i = 0; i < sum_list.length(); i++)
    {
      std::cout << sum_list[i] << ((i + 1 == sum_list.length()) ? "" : " ");
    }
    sum_list.clear();
    pair_list.clear();
    return 0;
  }
  catch (std::invalid_argument& e)
  {
    std::cerr << "Not a number in a number list\n";
    pair_list.clear();
    return 1;
  }
  catch (std::logic_error& e)
  {
    std::cerr << e.what();
    pair_list.clear();
    return 1;
  }
}
