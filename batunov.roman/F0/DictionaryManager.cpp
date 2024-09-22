#include "DictionaryManager.h"

void DictionaryManager::help() const {
    std::cout << "Доступные команды:\n"
              << "help - вывод списка доступных команд.\n"
              << "list - вывод названий всех существующих словарей.\n"
              << "create <dictionary1> - создание нового словаря.\n"
              << "delete <dictionary1> - удаление существующего словаря.\n"
              << "combine <dictionary1> <dictionary2> <dictionary3> - создать новый словарь.\n"
              << "add <dictionary1> <word1> - добавить слово в словарь.\n"
              << "definition <dictionary1> <word1> <слово1> - добавить перевод слова.\n"
              << "remove <dictionary1> <word1> - удалить слово из словаря.\n"
              << "translate <dictionary1> <word1> - вывод перевода слова.\n"
              << "size <dictionary1> - вывод количества слов в словаре.\n"
              << "show <dictionary1> - вывод всех слов в словаре.\n"
              << "random <dictionary1> - вывод случайного слова из словаря.\n";
}

void DictionaryManager::create(const std::string &name) {
    if (dictionaries.find(name) != dictionaries.end()) {
        throw std::runtime_error("Такой словарь уже существует");
    }
    Dictionary newDict(name);
    dictionaries[name] = newDict;
}

void DictionaryManager::combine(const std::string &dict1,
                                const std::string &dict2, const std::string &newDict)  {
    if (dictionaries.find(dict1) == dictionaries.end() ||
        dictionaries.find(dict2) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    if (dictionaries.find(newDict) != dictionaries.end()) {
        throw std::runtime_error("Такой словарь уже существует");
    }

    Dictionary combinedDict(newDict);
    for (const auto &word : dictionaries[dict1].getAllWords()) {
        combinedDict.addWord(word);
        for (const auto &translation : dictionaries[dict1].translate(word)) {
            combinedDict.addTranslation(word, translation);
        }
    }
    for (const auto &word : dictionaries[dict2].getAllWords()) {
        if (combinedDict.search(word) == nullptr) {
            combinedDict.addWord(word);
        }
        for (const auto &translation : dictionaries[dict2].translate(word)) {
            combinedDict.addTranslation(word, translation);
        }
    }
    dictionaries[newDict] = combinedDict;
}

void DictionaryManager::add(const std::string &dictName, const std::string &word){
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries[dictName].addWord(word);
}

void DictionaryManager::addTranslation(const std::string &dictName, const std::string &word,
                                       const std::string &translation)  {
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries[dictName].addTranslation(word, translation);
}

void DictionaryManager::translate(const std::string &dictName, const std::string &word) const {
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    const auto &translations = dictionaries.at(dictName).translate(word);
    for (const auto &t : translations) {
        std::cout << t << std::endl;
    }
}

void DictionaryManager::size(const std::string &dictName) const{
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    std::cout << "Количество слов в словаре '" << dictName << "': " <<
              dictionaries.at(dictName).getAllWords().size() << std::endl;
}

void DictionaryManager::random(const std::string &dictName) const {
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    const auto &words = dictionaries.at(dictName).getAllWords();
    if (!words.empty()) {
        int index = std::rand() % words.size();
        std::cout << "Случайное слово: " << words[index] << std::endl;

        auto translations = dictionaries.at(dictName).translate(words[index]);
        for (const auto &translation : translations) {
            std::cout << "Перевод: " << translation << std::endl;
        }
    } else {
        std::cout << "Словарь пуст." << std::endl;
    }
}

void DictionaryManager::removeWord(const std::string &dictName, const std::string &word) {
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries[dictName].removeWord(word);
}

void DictionaryManager::show(const std::string &dictName) const {
    if (dictionaries.find(dictName) == dictionaries.end()) {
        throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries.at(dictName).show();
}

void DictionaryManager::remove(const std::string &name)  {
    if (dictionaries.erase(name) == 0) {
        throw std::runtime_error("Такого словаря не существует");
    }
}
