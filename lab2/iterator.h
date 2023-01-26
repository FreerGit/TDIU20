#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator {
private:
  Node* ptr;

public:
  Iterator(); 
  Iterator(Node* ptr);

  bool operator!=(const Iterator& itr) const;
  int operator*() const;

  Iterator& operator++();
  Iterator operator++(int);
}; 

#endif