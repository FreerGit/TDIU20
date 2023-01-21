#ifndef NODE_H
#define NODE_H

class Node {
private:
    int data;
public:
    Node(int num);

    int get_data() const;
    Node* next;
    Node* prev;
};

#endif