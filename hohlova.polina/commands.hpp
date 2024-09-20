#include <iostream>
#include <map>
#include <string>
#include "AVLTree.hpp"
#include <unordered_map>
namespace hohlova
{
    template< typename T1, typename T2 >
    std::ostream& operator<<(std::ostream& os, const std::pair< T1, T2 >& p)
    {
        return os << "(" << p.first << ", " << p.second << ")";
    }

    using Dictionary = BinarySearchTree< std::string, std::string >;
    using DictOfDictionary = BinarySearchTree< std::string, Dictionary >;

    void help(std::ostream& stream);
    void create(DictOfDictionary& dictOfdict, std::istream& is);
    void size(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void view(DictOfDictionary& dictOfdict, std::ostream& out);
    void find(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void rename(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void edit(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void insert(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void remove(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void clear(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
    void save(DictOfDictionary& dictOfdict, std::ostream& out);

    void printError(const std::string& err);
}
