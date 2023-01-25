#include "node.h"

Node::Node(int const& num) : data{num}, next{nullptr}, prev{nullptr} {
    // this
}

int Node::get_data() const {
    return this->data;
}
