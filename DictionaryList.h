#pragma once
#pragma once
#include <string>

struct Node  // If Node is inside DictionaryList, the friend fuction doesn't see Node
{
	std::string key;
	std::string value;
	Node* next;

	Node() : next(nullptr) {}
	Node(const std::string& key, const std::string& value = "") : key(key), value(value), next(nullptr) {}
};

class DictionaryList
{
	Node* _head;

public:
	DictionaryList();  // Rule of Five
	DictionaryList(const DictionaryList& other) = delete;
	DictionaryList(DictionaryList&& other) noexcept;
	~DictionaryList();

	DictionaryList& operator=(const DictionaryList& other) = delete;
	DictionaryList& operator=(DictionaryList&& other) noexcept;

	void insert(const std::string& key, const std::string& value = "");
	void remove(const std::string& key, bool deleteWordsMethod = false);
	bool search(const std::string& key) const;

	void merge(DictionaryList& other);
	void deleteWords(const DictionaryList& other);
	friend void getIntersection(const DictionaryList& first, const DictionaryList& second, DictionaryList& res);

	void printContent() const;
};
