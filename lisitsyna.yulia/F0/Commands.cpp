#include "Commands.hpp"
#include <sstream>
void Commands::help(std::ostream &out) noexcept
{
  out << "1. help - выводит список команд\n"
         "2. openFile < filename > - открытие файла для чтения с заданным названием\n"
         "3. analyze < filename > < dictionary name > - анализ текста, сохранения результата в словарь с именем < dictionary name >\n"
         "4. closeFile - закрытие текущего файла для чтения\n"
         "6. print < dictionary name > - вывод таблицы слов и строк, в которых они встречаются, в консоль\n"
         "7. delete < key > < dictionary name > - удаление элемента из словаря\n"
         "8. exist < key > < dictionary name > - проверка словаря на наличие элемента с ключом key\n"
         "9. showSize < dictionary name > - вывод количества слов в словаре\n"
         "10. remove < dictionary name > - удаление словаря\n";
}
void Commands::open_new_input(str_const_ref filename)
{
  if (current_in.is_open())
  {
    current_in.close();
  }
  current_in.open(filename);
  if (!current_in.good())
  {
    throw std::runtime_error("Can't open stream");
  }
}
void Commands::open_file(std::istream &in)
{
  current_filename = get_1_parameters(in);
  open_new_input(current_filename);
}
std::string Commands::get_1_parameters(std::istream &in)
{
  std::string line;
  getline(in, line);
  std::istringstream new_in(line);
  std::string filename;
  new_in >> filename;
  return filename;
}
std::pair< std::string, std::string > Commands::get_2_parameters(std::istream &in)
{
  std::string line;
  getline(in, line);
  std::istringstream new_in(line);
  std::string filename, dict_name;
  new_in >> filename >> dict_name;
  return {filename, dict_name};
}
void Commands::analyze(std::istream &in)
{
  auto parameters = get_2_parameters(in);
  std::string filename = parameters.first;
  std::string dict_name = parameters.second;
  open_new_input(filename);
  auto *storage = &data.get(dict_name);
  std::string word;
  while (current_in >> word)
  {
    if (storage->contains(word))
    {
      storage->get(word)++;
    }
    else
    {
      storage->insert(word, 1);
    }
  }
}
void Commands::close_file(std::ostream &out) noexcept
{
  current_in.close();
  current_filename = "";
  if (!current_in.is_open())
  {
    out << "Success close\n";
  } else {
    out << "Not success close\n";
  }
}
void Commands::print(std::istream &in, std::ostream &out)
{
  data.get(get_1_parameters(in)).print(out);
}
void Commands::delete_func(std::istream &in)
{
  auto parameters = get_2_parameters(in);
  std::string key = parameters.first;
  std::string dict_name = parameters.second;
  data.get(dict_name).deleteKey(key);
}
void Commands::exist(std::istream &in, std::ostream &out)
{
  auto parameters = get_2_parameters(in);
  std::string key = parameters.first;
  std::string dict_name = parameters.second;
  out << "Contains key is " << data.get(dict_name).contains(key) << "\n";
}
void Commands::show_size(std::istream &in, std::ostream &out)
{
  std::string dict_name = get_1_parameters(in);
  out << "Size of " << dict_name << " is " << data.get(dict_name).getCount() << "\n";
}
void Commands::remove(std::istream &in)
{
  std::string dict_name = get_1_parameters(in);
  data.deleteKey(dict_name);
}
Commands::Commands():
  current_filename(),
  current_in(),
  base_functions(),
  base_functions_2()
{
  using namespace std::placeholders;
  base_functions.insert("help", std::bind(&Commands::help, this, _1));
  base_functions_1.insert("openFile", std::bind(&Commands::open_file, this, _1));
  base_functions_1.insert("analyze", std::bind(&Commands::analyze, this, _1));
  base_functions.insert("closeFile", std::bind(&Commands::close_file, this, _1));
  base_functions_2.insert("print", std::bind(&Commands::print, this, _1, _2));
  base_functions_1.insert("delete", std::bind(&Commands::delete_func, this, _1));
  base_functions_2.insert("exist", std::bind(&Commands::exist, this, _1, _2));
  base_functions_2.insert("showSize", std::bind(&Commands::show_size, this, _1, _2));
  base_functions_1.insert("remove", std::bind(&Commands::remove, this, _1));
}
void Commands::do_command(const std::string &command, std::istream &in, std::ostream &out)
{
  if (base_functions.contains(command))
  {
    base_functions.get(command)(out);
  }
  if (base_functions_1.contains(command))
  {
    base_functions_1.get(command)(in);
  }
  if (base_functions_2.contains(command))
  {
    base_functions_2.get(command)(in, out);
  }
}
