#include <initializer_list>
#include <optional>

#ifndef LIST_H
#define LIST_H

/*
  Information om komplettering:
  Eventuella siffrorna hänvisar till rättningsprotokollet som finns på: https://www.ida.liu.se/divisions/sas/groups/upp/info/lang/cpp/UPP_correct_guide.pdf

  Kompletteringen kan gälla hela filen och alla filer i labben, så får ni komplettering på en sak, kan samma sak förekomma på fler ställen utan att jag skrivit det.

  Komplettering lämnas in via sendlab efter senast en (1) vecka

  Har ni frågor om kompletteringen kan ni maila mig på:
  simon.ahrenstedt@liu.se
*/

/*

  Komplettering: Ni testar inte att ni löst fallet med självtilldelning.

*/


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

    Iterator begin();
    Iterator end();

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