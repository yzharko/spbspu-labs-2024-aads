#include <iostream>

template< typename T >
struct List
{
  T data;
  List< T > * next;
  List< T > * prev;
};

int main()
{
  List< int > * head = new List< int >{ 0, nullptr, nullptr };
  List< int > * tail = head;
  std::cout << head->data << "\n";
}
