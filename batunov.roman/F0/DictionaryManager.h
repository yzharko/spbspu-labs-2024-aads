
#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H
#include "Dictionary.h"

class DictionaryManager {
private:
    std::map<const std::string, Dictionary> dictionaries;
public:
    void help() const;

    void list() const {
        for (const auto &dict : dictionaries) {
            std::cout << dict.first << std::endl;
        }
    }

    void create(const std::string &name);

    void remove(const std::string &name);

    void combine(const std::string &dict1, const std::string &dict2, const std::string &newDict);

    void add(const std::string &dictName, const std::string &word);

    void addTranslation(const std::string &dictName, const std::string &word,
                        const std::string &translation);

    void removeWord(const std::string &dictName, const std::string &word);

    void translate(const std::string &dictName, const std::string &word) const;

    void size(const std::string &dictName) const;

    void show(const std::string &dictName) const;

    void random(const std::string &dictName) const;
};

#endif
