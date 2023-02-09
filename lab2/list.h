#include <initializer_list>
#include <optional>

#ifndef LIST_H
#define LIST_H

class List {
    class Iterator;

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
    std::optional<int> get(int const index) const;
    void clear();
    bool is_empty() const;

    std::optional<int> get_first() const;
    std::optional<int> get_last() const;
    int get_size() const;

    Iterator begin() const;
    Iterator end() const;

private:
    class Node {
    public:
        Node(int const& num);

        Node* next;
        Node* prev;
        int data;
    };

    class Iterator {
    public:
        Iterator(); 
        Iterator(Node* ptr);

        bool operator!=(const Iterator& itr) const;
        int operator*() const;

        Iterator& operator++();
        Iterator operator++(int);

        Node* ptr;
    }; 



    Node* first;
    Node* last;
    int size;
};

std::ostream& operator<<(std::ostream &os, List const &list);

#endif