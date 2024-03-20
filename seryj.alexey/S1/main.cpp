#include <iostream>
#include <string>
#include "Iterator.hpp"
#include "List.hpp"
int main()
{
  try
  {
    using pair = std::pair<std::string, List<int>>;
    List<pair> pair_list;
    size_t max_length = 0;
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
      return 0;
    for (size_t i = 0; i < pair_list.length(); i++)
    {
      std::cout << pair_list[i].first << " ";
    }
    std::cout << '\n';
    for (size_t i = 0; i < max_length; i++)
    {
      for (size_t j = 0; j < pair_list.length(); j++)
      {
        if (pair_list[j].second.length() > i)
          std::cout << pair_list[j].second[i] << " ";
      }
    }
    std::cout << '\n';
    size_t sum = 0;
    for (size_t i = 0; i < pair_list.length(); i++)
    {
      for (size_t j = 0; j < pair_list[i].second.length(); j++)
      {
        sum += pair_list[i].second[j];
      }
    }
    std::cout << sum;
    return 0;
  }
  catch (std::logic_error& e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch (std::invalid_argument)
  {
    std::cerr << "Not a number in a number list\n";
    return 1;
  }
}
