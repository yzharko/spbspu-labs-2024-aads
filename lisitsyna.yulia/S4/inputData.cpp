#include "inputData.hpp"

lisitsyna::data_t lisitsyna::input_dict(std::istream &input)
{
  data_t data;
  std::string name;
  while (input >> name)
  {
    dataset_t dict;
    int key = 0;
    std::string value;

    while (input >> key >> value)
    {
      dict.insert(std::make_pair(key, value));
    }
    if (!input.eof())
    {
      input.clear();
    }
    data.insert(std::make_pair(name, dict));
  }
  return data;
}
