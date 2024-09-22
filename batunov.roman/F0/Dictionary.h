#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "RedBlackTree.h"

class Dictionary {
private:
    std::string name;
    RedBlackTree tree;

public:
    explicit Dictionary(const std::string &name) : name(name) {}
    Dictionary() = default;
    void addWord(const std::string &word) {
        tree.insert(word);
    }

    void addTranslation(const std::string &word, const std::string &translation);

    void removeWord(const std::string &word) {
        tree.remove(word);
    }

    std::vector<std::string> translate(const std::string &word) const;

    void show() const {
        tree.show();
    }

    std::string getName() const {
        return name;
    }
    Node* search(const std::string & key) const
    {
        return tree.search(key);
    }

    std::vector<std::string> getAllWords() const {
        return tree.getAllWords();
    }

};

#endif
