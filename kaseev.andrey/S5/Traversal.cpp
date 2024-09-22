#include "Traversal.hpp"
#include "Sum.hpp"

void kaseev::traverseAscending(const BST< long long, std::string, std::less<long long> > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    kaseev::Sum keySumCounter;
    kaseev::Sum keySumCounter_ = tree.traverse_lnr(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void kaseev::traverseDescending(const BST< long long, std::string, std::less<long long> > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    kaseev::Sum keySumCounter;
    kaseev::Sum keySumCounter_ = tree.traverse_lnr(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void kaseev::traverseBreadth(const BST< long long, std::string, std::less<long long> > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    kaseev::Sum keySumCounter;
    kaseev::Sum keySumCounter_ = tree.traverse_breadth(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void kaseev::printResult(kaseev::Sum &keySumCounter, std::ostream &os) {
  os << keySumCounter.result_;

  while (!keySumCounter.queue.empty()) {
    const auto &kv = keySumCounter.queue.front();
    os << " " << kv.second;
    keySumCounter.queue.pop();
  }

  os << "\n";
}

void kaseev::emptyCommandWarning(std::ostream &out) {
  out << "<EMPTY>\n";
}

void kaseev::invalidCommandError(std::ostream &out) {
  out << "<INVALID COMMAND>\n";
}
