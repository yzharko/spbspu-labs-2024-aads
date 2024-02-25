#include <iostream>
#include <string>
#include "Iterator.hpp"
int main()
{
  using My_list = List<std::pair<std::string, List<int>*>>;
  using My_iterator = Iterator<std::pair<std::string, List<int>*>>;
  My_list* head;
  My_iterator my_iter;
  my_iter.node = new My_list{ {"",nullptr }, nullptr };
  while (!std::cin.eof())
  {
    std::string line;
    std::getline(std::cin, line);
    bool name = true;
    my_iter->second = new List<int>;
    Iterator<int> int_iter;
    int_iter.node = my_iter->second;
    for (int i = 0; i < line.length(); i++)
    {
      if (line[i] == ' ')
        name = false;
      else
      {
        if (name)
          my_iter->first += line[i];
        else
        {
          int_iter.node->data = (int)line[i];
          int_iter.node->next = new List<int>;
          int_iter++;
        }
      }
      my_iter.node->next = new My_list{ {"",nullptr }, nullptr };
      my_iter++;
    }
  }
  //delete my iter;
  my_iter.node = head;
  while (my_iter.node->next)
  {
    std::cout << my_iter->first << " ";
    my_iter++;
  }
  //delete my_iter;
  std::cout << '\n';
  my_iter.node = head;
}