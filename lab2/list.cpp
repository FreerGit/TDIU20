#include "list.h"
#include <stdexcept>
#include <iostream>

using namespace std;

List::List() : first(), last(), size{0} {
    first = nullptr;
    last = nullptr;
}

List::List(int num) : first(), last(), size() {
    this->insert(num);
}

List::List(initializer_list<int> l) : first(), last(), size() {
    if(l.size() == 0) {
        List();
    } else {
        for(int const num : l) {
            this->insert(num);
        }
    }
}

Node* List::get_first() const {
    return this->first;
}

Node* List::get_last() const {
    return this->last;
}

int List::get_size() const {
    return this->size;
}

void List::insert(int const num) {
    if(!this->first) {
        this->first = new Node(num);
        this->last = first;
    } else if (this->first->get_data() >= num) {
        Node* node = new Node(num);
        node->next = this->first;
        this->first = node;
    } else {
        if(this->last && this->last->get_data() <= num) {
            this->last->next = new Node(num);
            this->last = this->last->next;
        } else {
            Node* temp{this->first};
            Node* node = new Node(num);
            while(temp->next && temp->next->get_data() < node->get_data()) {
               temp = temp->next;
            }

            node->next = temp->next;
            if(temp->next) {
                node->next->prev = node;
            }
            
            temp->next = node;
            node->prev = temp;
        }
    }
    this->size++;
}

optional<int> List::get(int const index) {
    if(!this->first) {
        return {};
    }
    if(this->size - 1 == index) {
        return this->last->get_data();
    }
    Node* temp{this->first};

    int step{0};
    while(temp) {
        if(step == index) {
            return temp->get_data();
        } else {
            temp = temp->next;
            step++;
        }
    }
    
    return {};
}


std::ostream& operator<<(std::ostream &os, List const &list)
{
    Node* temp{list.get_first()};
    while(temp) {
        os << temp->get_data();
        temp = temp->next;
        if(temp) {
            os << " ";
        }
    }
    return os;
}