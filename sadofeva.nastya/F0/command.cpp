#include "command.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

namespace sadofeva
{
  struct isName
  {
    bool operator()(const Dict &dictionary, cnstStr &name)
    {
      return dictionary.getName() == name;
    }
  };

  std::ostream &operator<<(std::ostream &os, const Dict &dict)
  {
    return os;
  }

  std::istream &operator>>(std::istream &is, Dict &dict)
  {
    return is;
  }

  typedef sadofeva::AVLTree< std::string, int > WordFrequencyMap;
  sadofeva::AVLTree< std::string, WordFrequencyMap > dictionaries;
  std::vector< std::string > split(const std::string &input, char delimiter)
  {
    std::istringstream stream(input);
    std::istream_iterator< std::string > begin(stream), end;
    return {begin, end};
  }
  template< typename T >
  auto isFoundHelper(T &dicts, const cnstStr &name)
  {
    auto iter = std::find_if(dicts.begin(), dicts.end(), [&name](const Dict& dict) {
      return dict.getName() == name;
    });
    if (iter == dicts.end()) {
      throw std::invalid_argument("Dictionary " + name + " wasn't found.");
    }
    return iter;
  }

  auto isFound(const std::vector< Dict > &dicts, const cnstStr &name)
  {
    return isFoundHelper(dicts, name);
  }

  auto isFound(std::vector< Dict >&dicts, const cnstStr &name)
  {
    return isFoundHelper(dicts, name);
  }

  void insert(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string datasetName, word;
    input >> datasetName >> word;
    auto it = isFound(dicts, datasetName);
    if (it != dicts.end()) {
      it->insert(word);
      output << "Word '" << word << "' inserted into dataset '" << datasetName << "'." << '\n';
    } else {
      output << "Dataset not found." << '\n';
    }
  }

  void remove(std::istream &input, std::vector< Dict >& dicts)
  {
    std::string dataset, word;
    input >> dataset >> word;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      if (dictIt->deleteWord(word)) {
        std::cout << "Word removed." << '\n';
      } else {
        std::cout << "Word not found in the dataset" << '\n';
      }
    } else {
      std::cout << "Dataset not found" << '\n';
    }
  }

  void search(std::istream &input, std::ostream &output, const std::vector< Dict >& dicts)
  {
    std::string name, word;
    input >> name >> word;
    auto iter = isFound(dicts, name);
    output << int(iter->search(word) != iter->end());
    output << '\n';
  }

  void printMaxCountWords(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string dataset, word;
    input >> dataset >> word;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      auto result = dictIt->search(word);
      if (result != dictIt->end()) {
        output << "Frequency of word '" << word << "': " << result->second << '\n';
      } else {
        output << "Word not found in the dataset." << '\n';
      }
    } else {
      output << "Dataset not found" << '\n';
    }
  }

  void print(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string dataset;
    input >> dataset;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      dictIt->print(output);
    } else {
      output << "not found" << '\n';
    }
  }

  void save(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string dataset, path;
    input >> dataset >> path;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      std::ofstream outFile(path);
      if (outFile.is_open()) {
        dictIt->print(outFile);
        outFile.close();
        output << "Dataset saved to " << path << '\n';
        return;
      } else {
        output << "Failed to open file for saving" << '\n';
        return;
      }
    } else {
      output << "Dataset not found" << '\n';
      return;
    }
  }

  void load(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string dataset, path;
    input >> dataset >> path;
    Dict newDict;
    std::ifstream inFile(path, std::ios::in | std::ios::binary);
    if (inFile.is_open()) {
      inFile >> newDict;
      inFile.close();
      dicts.push_back(std::move(newDict));
      output << "Dataset loaded from " << path << '\n';
    } else {
      output << "Failed to open file for loading" << '\n';
    }
  }

  void getSize(const std::string &dataset, const std::vector< Dict >& dicts)
  {
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      std::cout << "Number of words in dataset '" << dataset << "': " << dictIt->getSum() << '\n';
    } else {
      std::cout << "Dataset not found" << '\n';
    }
  }

  void count(std::istream &input, std::ostream &output, const std::vector< Dict >& dicts)
  {
    std::string dataset;
    int count = 0;
    input >> dataset >> count;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      dictIt->printMostPopular(output);
    } else {
      output << "Dataset not found" << '\n';
    }
  }

  void clear(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string dataset;
    input >> dataset;
    auto dictIt = isFound(dicts, dataset);
    if (dictIt != dicts.end()) {
      dictIt->drop();
    } else {
      std::cout << "Dataset not found" << '\n';
    }
  }

  void intersectionCommand(std::vector< Dict >& dicts, cnstStr &name, cnstIter it1, cnstIter it2, cnstStr &cmd, char c)
  {
    Dict newDictionary(name);
    std::for_each(it1->begin(), it1->end(), [&](const std::pair< const std::string, size_t > &i) {
      auto item = it2->search(i.first);
      if (item != it2->end()) {
        if (i.second <= (*item).second) {
          newDictionary.insertPair(i);
        } else {
          newDictionary.insertPair(*item);
        }
      }
    });
    dicts.push_back(newDictionary);
  }

  void unionData(std::istream &input, std::ostream &output, std::vector< Dict >& dicts)
  {
    std::string newDataset;
    int numDatasets;
    input >> newDataset >> numDatasets;
    if (numDatasets < 2) {
      output << "You need at least 2 datasets to perform a union." << '\n';
      return;
    }
    std::vector< std::string > datasetsToUnion;
    for (size_t i = 0; i < numDatasets; ++i) {
      std::string datasetName;
      input >> datasetName;
      datasetsToUnion.push_back(datasetName);
    }

    Dict newUnionDict(newDataset);
    for (const std::string &dataset: datasetsToUnion) {
      auto dictIt = isFound(dicts, dataset);
      if (dictIt != dicts.end()) {
        for (auto &pair: *dictIt) {
          newUnionDict.insertPair(pair);
        }
      } else {
        output << "Dataset '" << dataset << "' not found" << '\n';
        return;
      }
    }
    dicts.push_back(std::move(newUnionDict));
    output << "Union saved as dataset '" << newDataset << "'." << '\n';
  }
}

