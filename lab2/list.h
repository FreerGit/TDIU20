#include "node.h"
#include <initializer_list>
#include <optional>

#ifndef LIST_H
#define LIST_H

class List {
public:
    List(); 
    List(int num);
    // this could also be a recursive constructor.
    List(std::initializer_list<int>); 

    void insert(int const num);
    void remove(int const index);
    std::optional<int> get(int const index);

    Node* get_first() const;
    Node* get_last() const;
    int get_size() const;

private:
    Node* first;
    Node* last;
    int size;
};

std::ostream& operator<<(std::ostream &os, List const &list);

#endif