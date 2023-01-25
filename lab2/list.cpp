#include "list.h"
#include <stdexcept>
#include <iostream>

using namespace std;

List::List() : first(), last(), size{0} {
    first = nullptr;
    last = nullptr;
}

List::List(initializer_list<int> const& l) : first(), last(), size() {
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
  
    else if (this->first->get_data() >= new_node->get_data()) {
        new_node->next = this->first;
        new_node->next->prev = new_node;
        this->first = new_node;
    }
  
    else {
        curr = this->first;
  
        while (curr->next && 
               curr->next->get_data() < new_node->get_data()) {
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
    ++this->size;
}

void List::remove(int const& index) {
    if(index == 0) {
        this->first = this->first->next;
    } else if (index == this->size -1) {
        Node* curr{this->last};
        this->last = curr->prev;
        this->last->next = nullptr;
        free(curr);
    } else {

        Node* curr = this->last;
        Node* prev = this->last;
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

optional<int> List::get(int const& index) {
    if(this->is_empty()) {
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
        // cout << temp << " data-> " << temp->get_data() << " next-> " << temp->next << " prev-> " << temp->prev << endl;
        
        os << temp->get_data();
        temp = temp->next;
        if(temp) {
            os << " ";
        }
    } 
    os << list.get_first()<< " " << list.get_last();
    return os;
}