#ifndef KEYSTRUCT_HPP
#define KEYSTRUCT_HPP
#include <string>
#include <utility>

namespace sadofeva
{
  struct KeyVal
  {
  public:
    KeyVal();
    void operator()(const std::pair< const int, std::string >& keyval);
    int get_key_sum() const;
    std::string get_val_sum();
  private:
    int keySum_;
    std::string valSum_;
  };
}

#endif
