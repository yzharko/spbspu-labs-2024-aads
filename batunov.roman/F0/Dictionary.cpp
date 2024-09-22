#include "Dictionary.h"

void Dictionary::addTranslation(const std::string &word, const std::string &translation){
    Node *node = tree.search(word);
    if (!node) {
        throw std::runtime_error("Такого слова не существует");
    }
    node->translations.push_back(translation);
}

std::vector<std::string> Dictionary::translate(const std::string &word) const{
    Node *node = tree.search(word);
    if (!node) {
        throw std::runtime_error("Такого слова не существует");
    }
    return node->translations;
}
