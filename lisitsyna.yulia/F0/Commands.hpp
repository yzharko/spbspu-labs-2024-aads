#ifndef COURSE_COMMANDS_H
#define COURSE_COMMANDS_H
#include <functional>
#include <fstream>
#include <utility>
#include "bintree.hpp"
using data_storage = AVLTree< std::string, AVLTree< std::string, int > >;
using data_storage_ref = data_storage &;
using str_const_ref = const std::string &;
class Commands
{
public:
  Commands();
  void do_command(const std::string &command, std::istream &in, std::ostream &out);
private:
  std::string current_filename;
  std::ifstream current_in;
  using base_func = std::function< void(std::ostream &) >;
  using base_func_1 = std::function< void(std::istream &) >;
  using base_func_2 = std::function< void(std::istream &, std::ostream &) >;
  data_storage data;
  AVLTree< std::string, base_func > base_functions;
  AVLTree< std::string, base_func_1 > base_functions_1;
  AVLTree< std::string, base_func_2 > base_functions_2;
  static std::string get_1_parameters(std::istream &in);
  static std::pair< std::string, std::string > get_2_parameters(std::istream &in);
  void help(std::ostream &out) noexcept;
  void open_new_input(str_const_ref filename);
  void open_file(std::istream &in);
  void analyze(std::istream &in);
  void close_file(std::ostream &out) noexcept;
  void print(std::istream &in, std::ostream &out);
  void delete_func(std::istream &in);
  void exist(std::istream &in, std::ostream &out);
  void show_size(std::istream &in, std::ostream &out);
  void remove(std::istream &in);
};
#endif
