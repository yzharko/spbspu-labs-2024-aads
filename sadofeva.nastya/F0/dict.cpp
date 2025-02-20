#include "dict.hpp"
#include <iomanip>
#include <numeric>
#include <ostream>
#include <streamguard.h>
#include <type_traits>
#include <utility>

namespace sadofeva
{
  Dict::Dict(const std::string &name):
    name_(name)
  {}

  bool Dict::operator==(const Dict &dict) const
  {
    return name_ == dict.name_ && Dict_ == dict.Dict_;
  }

  std::string Dict::getName() const
  {
    return name_;
  }

  std::size_t Dict::getSum() const
  {
    if (empty()) {
      return 0;
    }
    auto sumCount = [](std::size_t a, pairSS b) {
      return a + b.second;
    };
    std::size_t sum = std::accumulate(Dict_.begin(), Dict_.end(), 0, sumCount);
    return sum;
  }

  bool Dict::empty() const
  {
    return Dict_.empty();
  }

  void Dict::rename(const std::string &name)
  {
    name_ = name;
  }

  void Dict::print(std::ostream &stream) const
  {
    if (empty()) {
      return;
    }
    StreamGuard guard(stream);
    stream << name_ << '\n';
    for (auto i = Dict_.begin(); i != Dict_.end();) {
      printPair(stream, *i);
      stream << (++i != Dict_.end() ? "\n" : "");
    }
  }

  void Dict::printPair(std::ostream &stream, const pairSS &pair) const
  {
    const std::size_t sum = getSum();
    StreamGuard guard(stream);
    stream << std::fixed << std::setprecision(1);
    stream << pair.first << ": " << pair.second * 100.0 / sum << '%';
  }

  void Dict::printMostPopular(std::ostream &stream) const
  {
    pairSS top[3];
    for (auto &i: Dict_) {
      if (i.second > top[0].second) {
        top[2] = std::move(top[1]);
        top[1] = std::move(top[0]);
        top[0] = std::make_pair(i.first, i.second);
      } else if (i.second > top[1].second) {
        top[2] = std::move(top[1]);
        top[1] = std::make_pair(i.first, i.second);
      } else if (i.second > top[2].second) {
        top[2] = std::make_pair(i.first, i.second);
      }
    }
    StreamGuard guard(stream);
    stream << name_ << " 3 most popular:\n";
    for (std::size_t i = 0; i < 3; ++i) {
      if (!top[i].second) {
        break;
      }
      printPair(stream, top[i]);
      stream << (i != 2 && top[i + 1].second ? "\n" : "");
    }
  }

  void Dict::insert(const std::string &word)
  {
    auto iter = Dict_.find(word);
    if (iter != Dict_.end()) {
      Dict_[word]++;
    } else {
      Dict_[word] = 1;
    }
  }
  void Dict::insertPair(const pairSS pair)
  {
    if (search(pair.first) != end()) {
      Dict_[pair.first] += pair.second;
    } else {
      Dict_[pair.first] = pair.second;
    }
  }
  mapCosntIter Dict::search(const std::string &word) const
  {
    return Dict_.find(word);
  }
  mapIter Dict::search(const std::string &word)
  {
    return Dict_.find(word);
  }

  bool Dict::deleteWord(const std::string &word)
  {
    auto iter = search(word);
    if (iter != Dict_.end()) {
      Dict_.erase(word);
      return true;
    }
    return false;
  }
  void Dict::drop()
  {
    auto iter = Dict_.begin();
    auto toDelete = iter;
    while (iter != Dict_.end()) {
      toDelete = iter;
      iter++;
      deleteWord(toDelete->first);
    }
  }

  mapCosntIter Dict::begin() const
  {
    return Dict_.begin();
  }

  mapCosntIter Dict::end() const
  {
    return Dict_.end();
  }

  mapIter Dict::begin()
  {
    return Dict_.begin();
  }

  mapIter Dict::end()
  {
    return Dict_.end();
  }
}

