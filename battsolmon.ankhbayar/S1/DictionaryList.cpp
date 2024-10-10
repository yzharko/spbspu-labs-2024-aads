#include "DictionaryList.h"
#include <iostream>
DictionaryList::DictionaryList()
{
  _head = nullptr;
}
DictionaryList::DictionaryList(DictionaryList&& other) noexcept
{
  _head = other._head;
	other._head = nullptr;
}
DictionaryList::~DictionaryList()
{
  while (_head != nullptr)
	{
		Node* tmp = _head->next;
		delete _head;
		_head = tmp;
	}
}
DictionaryList& DictionaryList::operator=(DictionaryList&& other) noexcept
{
	_head = other._head;
	other._head = nullptr;
	return *this;
}
void DictionaryList::insert(const std::string& key, const std::string& value)
{
	Node* newNode = new Node(key, value);
	if (_head == nullptr)
	{
		_head = newNode;
	}
	else
	{
		Node* prev = nullptr;
		for (Node* node = _head; node != nullptr; node = node->next)
		{
			if (newNode->key == node->key)
			{
				delete newNode;
				break;
			}
			else if (newNode->key < node->key)
			{
				newNode->next = node;
				if (prev == nullptr)
				{
					_head = newNode;
				}
				else
				{
					prev->next = newNode;
				}
				break;
			}
			else if (node->next == nullptr)
			{
				node->next = newNode;
				break;
			}
			prev = node;
		}
	}
}
void DictionaryList::remove(const std::string& key, bool deleteWordsMethod)
{
	Node* prev = nullptr;
	bool flag = false;
    Node* toDelete = nullptr;
	for (Node* node = _head; node != nullptr; node = node->next)
	{
		if (node->key == key)
		{
			flag = true;
			toDelete = node;
			if (prev == nullptr)
			{
				_head = node->next;
			}
			else if (node->next != nullptr)
			{
				prev->next = node->next;
			}
			else 
			{
				prev->next = nullptr;
			}
			node->next = nullptr;
			break;
		}
		prev = node;
	}
	if ((!flag) && (!deleteWordsMethod))
	{
		std::cerr << "The word which you want to delete is not in the dictionary anyway!" << std::endl;
	}
	else
	{
		delete toDelete;
	}
}
bool DictionaryList::search(const std::string& key) const
{
	for (Node* node = _head; node != nullptr; node = node->next)
	{
		if (node->key == key)
		{
			return true;
		}
	}
	return false;
}
void DictionaryList::merge(DictionaryList& other)
{
	while (other._head != nullptr)
	{
		this->insert(other._head->key, other._head->value);
		Node* tmp = other._head;
		other._head = other._head->next;
		delete tmp;
	}
}
void DictionaryList::deleteWords(const DictionaryList& other)
{
	Node* current = other._head;
	while (current != nullptr)
	{
		this->remove(current->key, true);
		current = current->next;
	}
}
void getIntersection(const DictionaryList& first, const DictionaryList& second, DictionaryList& res)
{
	Node* prev = nullptr;
	for (Node* node = second._head; node != nullptr; node = node->next)
	{
		if (first.search(node->key))
		{
			if (prev == nullptr)
			{
				res._head = new Node(node->key, node->value);
				prev = res._head;
			}
			else
			{
				prev->next = new Node(node->key, node->value);
				prev = prev->next;
			}
		}
	}
}
void DictionaryList::printContent() const
{
	std::cout << "Dictionary content in the {<key> : <value>} format:" << std::endl;
	for (Node* node = _head; node != nullptr; node = node->next)
	{
		std::cout << node->key << " : " << node->value << std::endl;
	}
}