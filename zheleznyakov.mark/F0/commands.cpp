#include "commands.hpp"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <limits>

std::string zheleznyakov::statusString(std::string msg, std::string status)
{
  return "[" + status + "] " + msg;
}

std::string zheleznyakov::prompt(std::string active)
{
  return active == "" ? "menu> " : "(" + active + ")> ";
}

std::ostream & zheleznyakov::commands::help(std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    out << statusString("No additional args allowed\n", "warn");
    throw std::logic_error("");
  }

  return out << "F0 - Cross-references\n"
  << "\n"
  << "Available menu commands:\n"
  << "  help                        List available commands\n"
  << "  list                        List saved strings\n"
  << "  create < title >            Create an empty string\n"
  << "  rm < title >                Remove the string\n"
  << "  cmp < title1 > < title2 >   Compare two strings, and list simular words\n"
  << "  diff < title1 > < title2 >  Compare two strings, and list different words\n"
  << "  enter < title >             Switch to the 'string' mode\n"
  << "\n"
  << "Available string commands:\n"
  << "  read (-f < filename >)      Reads string from stdin or a file\n"
  << "  table (-f < filename >)     Writes a word table to an stdout or a file\n"
  << "  info < word >               Prints an info for a word: count in the present string and its coordinates\n"
  << "  stats                       Print an overall string stats: total words count and an unique words count\n"
  << "  quit                        Quit from a 'string' mode\n";
}

std::ostream & zheleznyakov::commands::list(strings_t & strings, std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    out << statusString("No additional args allowed\n", "warn");
    throw std::logic_error("");
  }

  out << "Total: " << strings.getSize() << "\n";
  if (!strings.empty())
  {
    out << "\nNames:\n";
    std::transform(
      strings.begin(),
      strings.end(),
      std::ostream_iterator<std::string>(out, "\n"),
      extractKeyFromStringsPair
    );
  }
  return out;
}

std::ostream & zheleznyakov::commands::rm(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string keyToDelete = "";
  in >> keyToDelete;
  if (strings.find(keyToDelete) == strings.end())
  {
    out << statusString("Key not found\n", "warn");
    throw std::logic_error("");
  }
  strings.erase(keyToDelete);
  return out;
}

std::ostream & zheleznyakov::commands::create(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string keyToCreate = "";
  in >> keyToCreate;
  if (strings.find(keyToCreate) != strings.end())
  {
    out << statusString("Key is already in the list\n", "warn");
    throw std::logic_error("");
  }
  string_t data;
  strings.insert(keyToCreate, data);
  return out;
}

std::ostream & zheleznyakov::commands::cmp(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string l1 = "";
  in >> l1;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l1) == strings.end())
  {
    out << statusString("Key 1 is not found\n", "error");
    throw std::logic_error("");
  }
  std::string l2 = "";
  in >> l2;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l2) == strings.end())
  {
    out << statusString("Key 2 is not found\n", "error");
    throw std::logic_error("");
  }
  wordpairs_t s1 = strings.at(l1).second;
  wordpairs_t s2 = strings.at(l2).second;
  std::vector<std::string> matches;
  std::transform(
    s1.begin(),
    s1.end(),
    std::back_inserter(matches),
    extractKeyFromWordpair
  );
  std::sort(matches.begin(), matches.end());
  auto last = std::unique(matches.begin(), matches.end());
  std::copy_if(
    matches.begin(),
    last,
    std::ostream_iterator < std::string > (out, "\n"),
    std::bind(hasWord, s2, std::placeholders::_1)
  );
  return out;
}

bool zheleznyakov::hasWord(const wordpairs_t & ref, const std::string word)
{
  return ref.find(word) != ref.cend();
}

std::ostream & zheleznyakov::commands::diff(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string l1 = "";
  in >> l1;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l1) == strings.end())
  {
    out << statusString("Key 1 is not found\n", "error");
    throw std::logic_error("");
  }
  std::string l2 = "";
  in >> l2;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l2) == strings.end())
  {
    out << statusString("Key 2 is not found\n", "error");
    throw std::logic_error("");
  }
  wordpairs_t s1 = strings.at(l1).second;
  wordpairs_t s2 = strings.at(l2).second;
  std::vector<std::string> onlyInL1;
  std::transform(
    s1.begin(),
    s1.end(),
    std::back_inserter(onlyInL1),
    extractKeyFromWordpair
  );
  std::sort(onlyInL1.begin(), onlyInL1.end());
  auto last1 = std::unique(onlyInL1.begin(), onlyInL1.end());
  out << "Only in '" << l1 << "':\n";
  std::copy_if(
    onlyInL1.begin(),
    last1,
    std::ostream_iterator<std::string>(out, "\n"),
    std::bind(hasNoWord, s2, std::placeholders::_1)
  );
  out << "\nOnly in '" << l2 << "':\n";
  std::vector<std::string> onlyInL2;
  std::transform(
    s2.begin(),
    s2.end(),
    std::back_inserter(onlyInL2),
    extractKeyFromWordpair
  );
  std::sort(onlyInL2.begin(), onlyInL2.end());
  auto last2 = std::unique(onlyInL2.begin(), onlyInL2.end());
  std::copy_if(
    onlyInL2.begin(),
    last2,
    std::ostream_iterator<std::string>(out, "\n"),
    std::bind(hasNoWord, s1, std::placeholders::_1)
  );

  return out;
}

bool zheleznyakov::hasNoWord(const wordpairs_t & ref, const std::string word)
{
  return ref.find(word) == ref.cend();
}

std::ostream & zheleznyakov::commands::enter(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (active != "")
  {
    out << statusString("Already in string mode\n", "error");
    throw std::logic_error("");
  }
  std::string toEnter = "";
  in >> toEnter;
  if (strings.find(toEnter) == strings.end())
  {
    out << statusString("Key is not in the list\n", "error");
    throw std::logic_error("");
  }
  active = toEnter;
  return out;
}

std::ostream & zheleznyakov::commands::read(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (active == "")
  {
    out << statusString("Not in string mode\n", "error");
    throw std::logic_error("");
  }
  if (in.peek() != '\n')
  {
    std::string flag = "";
    in >> flag;
    if (flag != "-f")
    {
      out << statusString("No known flag is passed\n", "error");
      throw std::logic_error("");
    }
    std::string filename = "";
    in >> filename;
    std::ifstream fin(filename);
    if (!fin)
    {
      out << statusString("Unable to read the file\n", "error");
      throw std::logic_error("");
    }
    std::string contents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    wordpairs_t pairs = getDict(contents);
    string_t currentStruct{ contents, pairs };
    strings[active] = currentStruct;
  }
  else
  {
    std::string contents;
    std::string line;
    while (std::getline(in, line)) {
      if (line == "end")
      {
        break;
      }
      contents += line + '\n';
    }
    wordpairs_t pairs = getDict(contents);
    string_t currentStruct{ contents, pairs };
    strings[active] = currentStruct;
  }
  return out;
}

std::ostream & zheleznyakov::commands::table(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (active == "")
  {
    out << statusString("Not in string mode\n", "error");
    throw std::logic_error("");
  }
  if (in.peek() != '\n')
  {
    std::string flag = "";
    in >> flag;
    if (flag != "-f")
    {
      out << statusString("No known flag is passed\n", "error");
      throw std::logic_error("");
    }
    std::string filename = "";
    in >> filename;
    std::ofstream fout(filename);
    const wordpairs_t pairs = strings.at(active).second;
    std::transform(
      pairs.cbegin(),
      pairs.cend(),
      std::ostream_iterator < std::string > (fout, "\n"),
      wordEntryToString
    );
  }
  else
  {
    const wordpairs_t pairs = strings.at(active).second;
    std::transform(pairs.cbegin(), pairs.cend(), std::ostream_iterator < std::string >(out, "\n"), wordEntryToString);
  }
  return out;
}

std::ostream & zheleznyakov::commands::info(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  std::string word = "";
  in >> word;
  string_t currentString = strings.at(active);
  if (currentString.second.find(word) == currentString.second.end())
  {
    out << statusString("Word is not found\n", "error");
    throw std::logic_error("");
  }
  wordpair_t currentWord = currentString.second[word];
  out << word << '\n'
  << "Repeats: " << currentWord.getSize() << '\n'
  << "Coords:\n";
  std::ostream_iterator<std::string> out_iter(out, "\n");
  std::transform(
    currentWord.begin(),
    currentWord.end(),
    out_iter,
    coordsToPairs
  );
  return out;
}

std::ostream & zheleznyakov::commands::stats(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    out << statusString("No additional args allowed\n", "warn");
    throw std::logic_error("");
  }
  string_t currentString = strings.at(active);
  out << "Total words in dict: " << currentString.second.getSize() << '\n'
  << "Total chars: " << currentString.first.size() << "\n";
  return out;
}

std::ostream & zheleznyakov::commands::quit(std::string & active, std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    out << statusString("No additional args allowed\n", "warn");
    throw std::logic_error("");
  }
  if (active == "")
  {
    out << statusString("Already in menu\n", "warn");
    throw std::logic_error("");
  }
  active = "";
  return out;
}

std::string zheleznyakov::extractKeyFromStringsPair(const std::pair< std::string, string_t > & pair)
{
  return pair.first;
}

std::string zheleznyakov::extractKeyFromWordpair(const std::pair< std::string, wordpair_t > & pair)
{
  return pair.first;
}

std::string zheleznyakov::coordsToPairs(const wordcoord_t & wordCoord)
{
  return std::to_string(wordCoord.first) + ';' + std::to_string(wordCoord.second);
}

std::string zheleznyakov::wordEntryToString(const std::pair< std::string, wordpair_t >& pair)
{
    return pair.first + ':' + std::to_string(pair.second.getSize());
}
