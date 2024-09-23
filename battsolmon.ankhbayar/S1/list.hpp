#ifndef LIST_HPP
#define LIST_HPP
#include <ostream>
template <typename T>

class List
{
private:
	template <typename U>
	struct Node
	{
		Node(const T& data) :
			data_(data)
		{}
		T data_;
		Node<T>* next_{ nullptr };
	};
public:
	~List();
	bool insert(const T& data);
	bool insertToEnd(const T& data);
	bool insertUnique(const T& data);
	bool insertInOrder(const T& data);
	bool search(const T& data);
	bool remove(const T& data);

	void merge(List<T>& list);
	void deleteWords(const List<T>& list);
	template <typename U>
	friend List<U> getIntersection(List<U>& firstDict, List<U>& secondDict);
	template <typename U>
	friend std::ostream& operator<< (std::ostream& out, const List<U>& list);
private:
	Node<T>* head_{ nullptr };
};

template <typename T>
List<T>::~DictionaryList()
{
	if (head_)
	{
		while (head_->next_)
		{
			Node<T>* current = head_;
			head_ = head_->next_;
			delete current;
		}
		delete head_;
	}
}
template <typename T>
bool List<T>::insert(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		Node<T>* node = new Node<T>(data);
		node->next_ = head_;
		head_ = node;
		isAdded = true;
	}
	return isAdded;
}
template <typename T>
std::ostream& operator<< (std::ostream& out, const List<T>& list)
{
	typename List<T>::template Node<T>* current = list.head_;
	while (current)
	{
		if (current->next_)
		{
			out << current->data_ << ", ";
		}
		else
		{
			out << current->data_ << "\n";
		}
		current = current->next_;
	}
	return out;
}

template <typename T>
bool List<T>::insertToEnd(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		Node<T>* current = head_;
		while (current->next_)
		{
			current = current->next_;
		}
		Node<T>* node = new Node<T>(data);
		current->next_ = node;
		isAdded = true;
	}
	return isAdded;
}

template <typename T>
bool List<T>::insertUnique(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		bool isSameFound = false;
		Node<T>* current = head_;
		while (current)
		{
			if (current->data_ == data)
			{
				isSameFound = true;
				break;
			}
			current = current->next_;
		}
		if (!isSameFound)
		{
			Node<T>* node = new Node<T>(data);
			node->next_ = head_;
			head_ = node;
			isAdded = true;
		}
	}
	return isAdded;
}

template <typename T>
bool List<T>::insertInOrder(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		Node<T>* current = head_;
		if (current->data_ > data)
		{
			Node<T>* node = new Node<T>(data);
			node->next_ = head_;
			head_ = node;
			isAdded = true;
		}
		while (current)
		{
			if (((current->data_ < data) && (!current->next_)) || ((current->data_ < data) && (current->next_->data_ > data)))
			{
				if (!isAdded)
				{
					Node<T>* node = new Node<T>(data);
					node->next_ = current->next_;
					current->next_ = node;
					isAdded = true;
				}
			}
			current = current->next_;
		}
	}
	return isAdded;
}

template <typename T>
bool List<T>::search(const T& data)
{
	bool isFound = false;
	Node<T>* current = head_;
	while (current)
	{
		if (current->data_ == data)
		{
			isFound = true;
		}
		current = current->next_;
	}
	return isFound;
}

template <typename T>
bool List<T>::remove(const T& data)
{
	bool isDeleted = false;
	Node<T>* current = head_;
	Node<T>* temp = nullptr;
	if (current->data_ == data)
	{
		temp = head_;
		head_ = current->next_;
		current = head_;
		delete temp;
		isDeleted = true;
	}
	while (current->next_ && !isDeleted)
	{
		if (current->next_->data_ == data)
		{
			temp = current->next_;
			current->next_ = current->next_->next_;
			delete temp;
			isDeleted = true;
		}
		if (current->next_)
		{
			current = current->next_;
		}
	}
	return isDeleted;
}

template <typename T>
void List<T>::merge(List<T>& list)
{
	while (list.head_)
	{
		if (!search(list.head_->data_))
		{
			T data = list.head_->data_;
			Node<T>* currentFirst = head_;
			if (currentFirst->data_ > data)
			{
				Node<T>* node = list.head_;
				list.head_ = list.head_->next_;
				node->next_ = head_;
				head_ = node;

				currentFirst = currentFirst->next_;
			}
			while (currentFirst)
			{
				if (((currentFirst->data_ < data) && (!currentFirst->next_)) || ((currentFirst->data_ < data) && (currentFirst->next_->data_ > data)))
				{
					Node<T>* node = list.head_;
					list.head_ = list.head_->next_;
					node->next_ = currentFirst->next_;
					currentFirst->next_ = node;
				}
				currentFirst = currentFirst->next_;
			}
		}
		else
		{
			list.head_ = list.head_->next_;
		}
	}

}
template <typename T>
void List<T>::deleteWords(const List<T>& list)
{
	Node<T>* current = list.head_;
	while (current)
	{
		remove(current->data_);
		current = current->next_;
	}
}

template <typename T>
List<T> getIntersection(List<T>& firstDict, List<T>& secondDict)
{
	typename List<T>::template Node<T>* current = firstDict.head_;
	List<T> result;
	secondDict.search(current->data_);
	while (current)
	{
		if (secondDict.search(current->data_))
		{
			result.insertInOrder(current->data_);
		}
		current = current->next_;
	}
	return result;
}
#endif // !LIST_HPP
