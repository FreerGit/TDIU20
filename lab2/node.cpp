#include "node.h"

Node::Node(int num) : data{num}, next{nullptr}, prev{nullptr} {
    // this
}

int Node::get_data() const {
    return this->data;
}
