#include "list.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

List::Node::Node(int const& num) : next{nullptr}, prev{nullptr}, data{num} {}

List::List() : first{nullptr}, last{nullptr}, size{0} {}

List::List(initializer_list<int> const& l) : first(), last(), size() {
    if(l.size() == 0) {
        List();
    } else {
        for(int const num : l) {
            this->insert(num);
        }
    }
}

List::List(List &&l) : List() {
    *this = move(l);
}

List::List(List const& l) : List() {
    Node* node = l.first;
    while(node) {
        this->insert(node->data);
        node = node->next;
    }
}


List& List::operator=(List const &l)
{   
    if(this != &l) {
        clear();
        Node* node = l.first;
        while(node) {
            this->insert(node->data);
            node = node->next;
        }
    }
    return *this;
}

List& List::operator=(List &&l)
{
    if(this != &l) {
        swap(l.first, this->first);
        swap(l.last, this->last);
        swap(l.size, this->size);
    }
    return *this;
}


List::~List() {
    clear();
}

optional<int> List::get_first() const {
    if(this->first) {
        return this->first->data;
    } else {
        return {};
    }
}

optional<int> List::get_last() const {
    if(this->last) {
        return this->last->data;
    } else {
        return {};
    }
}

int List::get_size() const {
    return this->size;
}

void List::clear() {
    Node* curr = this->first;
    while(curr) {
        curr = curr->next;
        delete this->first;
        this->first = curr;
    }
    this->last = nullptr;
    this->size = 0;
}

bool List::is_empty() const {
    return (!this->first && !this->last);
}

void List::insert(int const& num) {
    Node* curr;
    Node* new_node = new Node(num);
  
    if (this->is_empty()){
        this->first = new_node;
        this->last = this->first;
    }
  
    else if (this->first->data >= new_node->data) {
        new_node->next = this->first;
        new_node->next->prev = new_node;
        this->first = new_node;
    }

    // performance boost for push_back
    else if (this->last->data <= new_node->data) {
        new_node->prev = this->last;
        this->last->next = new_node;
        this->last = new_node;
    }

    else {
        curr = this->first;
  
        while (curr->next && 
               curr->next->data < new_node->data) {
            curr = curr->next;
        }
  
        new_node->next = curr->next;

        if (curr->next) {
            new_node->next->prev = new_node;
        }
        else {
            this->last = new_node;
        }
  
        curr->next = new_node;
        new_node->prev = curr;
    }
    this->size++;
}

void List::remove(int const& index) {
    if(index == 0) {
        Node* curr{this->first};
        this->first = this->first->next;
        delete curr;
    } else if (index == this->size -1) {
        Node* curr{this->last};
        this->last = curr->prev;
        this->last->next = nullptr;
        delete curr;
    } else {

        Node* curr = this->first;
        Node* prev = this->first;
        int step{0};

        while (step != index)
        {
            prev = curr;
            curr = curr->next;
            ++step;
        }

        Node* after = curr->next;
        prev->next = after;

        if (after != NULL)
        {
            after->prev = prev;
        }

        delete curr;
    }
    this->size--;
}

optional<int> List::get(int const index) const {
    if(this->is_empty()) {
        return {};
    }
    if(this->size - 1 == index) {
        return this->last->data;
    }
    Node* temp{this->first};

    int step{0};
    while(temp) {
        if(step == index) {
            return temp->data;
        } else {
            temp = temp->next;
            step++;
        }
    }
    
    return {};
}


std::ostream& operator<<(std::ostream &os, List const &list)
{
    for (int i = 0; i < list.get_size(); i++)
    {
        os << list.get(i).value();
        if (i + 1 != list.get_size()) {
            os << " ";
        }
    }
  return os;
}

List::Iterator::Iterator() : ptr(nullptr) {} 
List::Iterator::Iterator(Node* ptr) : ptr(ptr) {}

bool List::Iterator::operator!=(const Iterator& itr) const {
  return ptr != itr.ptr;
} 

int List::Iterator::operator*() const {
  return ptr->data;
}

List::Iterator& List::Iterator::operator++() {
  ptr = ptr->next;
  return *this;
}

List::Iterator List::Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}



List::Iterator List::begin() {
    return Iterator(this->first);
}

List::Iterator List::end() {
    return Iterator(nullptr);
}
