#include "node.h"
#include "iterator.h"
#include <initializer_list>
#include <optional>

#ifndef LIST_H
#define LIST_H

class List {
public:
    List(); //empty
    List(std::initializer_list<int> const& list); // n
    List(List &&l); // Move
    List(List const& l); // Copy
    ~List(); //destructor

    List &operator=(List &&l); // Move assignment
    List &operator=(List const &l); // Copy assignment

    void insert(int const& num);
    void remove(int const& index);
    std::optional<int> get(int const& index);
    void clear();
    bool is_empty() const;

    Node* get_first() const;
    Node* get_last() const;
    int get_size() const;

    // iterator
    Iterator begin() cons
    Iterator end() const;

private:
    Node* first;
    Node* last;
    int size;
};

std::ostream& operator<<(std::ostream &os, List const &list);

#endif