#include "DictionaryList.h"
#include <iostream>
#include <utility>

void testDictionaryListOperations();
void testDictionaryListActions();

int main()
{
  setlocale(LC_ALL, "ru");
  testDictionaryListOperations();
  std::cout << "\n-------------------------------------------------\n\n";
  testDictionaryListActions();
  return 0;
}
void testDictionaryListOperations()
{
  DictionaryList dict1;  // Dictionary №1 that stores data about John - creating the empty dictionary
  std::cout << "1) CREATING THE EMPTY DICTIONARY №1:\n";
  dict1.printContent();
  std::cout << std::endl;
  dict1.insert("name", "John");  // Just inserting some data in №1 dictionary
  dict1.insert("age", "25");
  dict1.insert("city", "New York");
  dict1.insert("fav colour", "black");
  dict1.insert("cat", "Beans");
  dict1.insert("dog", "Brodie");
  std::cout << "2) DICTIONARY №1 AFTER INSERTING SOME DATA:\n";
  dict1.printContent();
  std::cout << std::endl;
  dict1.insert("name", "Sam");  // Trying to insert the existing word (key) - nothing changes
  std::cout << "3) DICTIONARY №1 AFTER TRYING TO INSERT THE EXISTING WORD (KEY):\n";
  dict1.printContent();
  std::cout << std::endl;
  dict1.remove("fav colour");  // Trying to delete some words
  std::cout << "4) DICTIONARY №1 AFTER DELETING THE WORD 'FAV COLOUR':\n";
  dict1.printContent();
  std::cout << std::endl;
  dict1.remove("age");  // Trying to delete some words
  std::cout << "5) DICTIONARY №1 AFTER DELETING THE WORD 'AGE':\n";
  dict1.printContent();
  std::cout << std::endl;
  dict1.remove("name");  // Trying to delete some words
  std::cout << "6) DICTIONARY №1 AFTER DELETING THE WORD 'NAME':\n";
  dict1.printContent();
  std::cout << std::endl;
  std::cout << "7) DICTIONARY №1 AFTER DELETING THE WORD 'COW':\n";  // Trying to delete unexciting words
  dict1.remove("cow");
  dict1.printContent();
  std::cout << std::endl;
  std::cout << "8) THE WORD 'DOG' IS IN THE №1 DICTIONARY: " << dict1.search("dog") << std::endl;  // Testing search method
  std::cout << "   THE WORD 'NAME' IS IN THE №1 DICTIONARY: " << dict1.search("name") << std::endl;
}

void testDictionaryListActions()
{
  DictionaryList dict1;
  dict1.insert("name", "John");  // The same dictionary about John from the testDictionaryListOperations()
  dict1.insert("age", "25");
  dict1.insert("city", "New York");
  dict1.insert("fav colour", "black");
  dict1.insert("cat", "Beans");
  dict1.insert("dog", "Brodie");
  std::cout << "1) INSERTING SOME DATA IN DICT1:" << std::endl;
  dict1.printContent();
  std::cout << std::endl;

  DictionaryList dict2;
  dict2.insert("name", "Liz");  // The same dictionary about Liz from the testDictionaryListOperations()
  dict2.insert("age", "20");
  dict2.insert("city", "New York");
  dict2.insert("fav colour", "black");
  dict2.insert("parrot", "Beans");
  dict2.insert("1", "2");
  std::cout << "2) INSERTING SOME DATA IN DICT2:" << std::endl;
  dict2.printContent();
  std::cout << std::endl;

  dict1.merge(dict2);  // Testing merge method
  std::cout << "3) TESTING MERGE METHOD FOR DICT1 AND DICT2:" << std::endl;
  std::cout << "DICT1:" << std::endl;
  dict1.printContent();
  std::cout << std::endl;
  std::cout << "DICT2:" << std::endl;
  dict2.printContent();
  std::cout << std::endl;

  DictionaryList dict3;  // Testing deleteWords method
  dict3.insert("name");
  dict3.insert("city");
  dict1.deleteWords(dict3);
  std::cout << "4) TESTING DELETEWORDS METHOD:" << std::endl;
  std::cout << "DICT3:" << std::endl;
  dict3.printContent();
  std::cout << std::endl;
  std::cout << "DICT1 AFTER DELETING WORDS FROM DICT3:" << std::endl;
  dict1.printContent();
  std::cout << std::endl;

  dict3.insert("cat");  // Testing getIntersection friend function
  dict3.insert("parrot");
  DictionaryList dict4;  // Creating dict4 outside getIntersection so that we don't return the local var
  getIntersection(dict1, dict3, dict4);
  std::cout << "5) TESTING GETINTERSECTION FRIEND FUNCTION (DICT4 = DICT1 & DICT3):" << std::endl;
  std::cout << "DICT1:" << std::endl;
  dict1.printContent();
  std::cout << std::endl;
  std::cout << "DICT3:" << std::endl;
  dict3.printContent();
  std::cout << std::endl;
  std::cout << "DICT4:" << std::endl;
  dict4.printContent();
  std::cout << std::endl;

  DictionaryList dict5(std::move(dict4));  // Testing move-constructor
  std::cout << "6) TESTING MOVE-CONSTRUCTOR (DICT5(STD::MOVE(DICT4))):" << std::endl;
  std::cout << "DICT5:" << std::endl;
  dict5.printContent();
  std::cout << std::endl;
  std::cout << "DICT4:" << std::endl;
  dict4.printContent();
  std::cout << std::endl;

  DictionaryList dict6;  // Testing move assignment operator
  dict6 = std::move(dict5);
  std::cout << "7) TESTING MOVE ASSIGNMENT OPERATOR (DICT6 = STD::MOVE(DICT5)):" << std::endl;
  std::cout << "DICT6:" << std::endl;
  dict6.printContent();
  std::cout << std::endl;
  std::cout << "DICT5:" << std::endl;
  dict5.printContent();
  std::cout << std::endl;
}
