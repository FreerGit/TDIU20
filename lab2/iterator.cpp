#include "node.h"
#include "iterator.h"

Iterator::Iterator() : ptr(nullptr) {} 
Iterator::Iterator(Node* ptr) : ptr(ptr) {}

bool Iterator::operator!=(const Iterator& itr) const {
  return ptr != itr.ptr;
} 

int Iterator::operator*() const {
  return ptr->get_data();
}

Iterator& Iterator::operator++() {
  ptr = ptr->next;
  return *this;
}

Iterator Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

