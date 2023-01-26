#include "catch.hpp"
#include "list.h"
#include <sstream>
#include <iostream>

using namespace std;

TEST_CASE ("Constructors") {
    SECTION("Default construtor") {
        List empty{};
        CHECK(empty.get_first() == nullptr);
        CHECK(empty.get_last() == nullptr);
    }

    SECTION("Constructor with one arg") {
        List one{5};
        CHECK(one.get_first()->get_data() == 5);
        CHECK(one.get_last()->get_data() == 5);
    }

    SECTION("Construtor with n args") {
        List mult{1,2,3,4,5,6};
        CHECK(mult.get_first()->get_data() == 1);
        CHECK(mult.get_last()->get_data() == 6);
        CHECK(mult.get_first()->next->next->get_data() == 3);
        CHECK(mult.get_size() == 6);
    }

    SECTION("Move") {
        stringstream ss;
        List l1{1,2,3};
        List l2{move(l1)};

        ss << l2;

        CHECK(l1.is_empty());
        CHECK(ss.str() == "1 2 3");

    }

    SECTION("Copy") {
        stringstream ss1;
        stringstream ss2;
        List l1{1,2,3};
        List l2 = l1;

        ss1 << l1;
        ss2 << l2;
        
        CHECK(ss1.str() == "1 2 3");
        CHECK(ss2.str() == "1 2 3");
    }
}

TEST_CASE("Public functions") {
    SECTION("get_first") {
        List many{1,2,3};
        
        CHECK(many.get_first()->get_data() == 1);
    }

    SECTION("get_last") {
        List many{1,2,3};

        CHECK(many.get_last()->get_data() == 3);
    }

    SECTION("get_size") {
        List empty{};
        List one{5};
        List many{1,2,3,3,3,3,3,3,3,3,3};

        CHECK(empty.get_size() == 0);
        CHECK(one.get_size() == 1);
        CHECK(many.get_size() == 11);
    }

    SECTION("is_empty") {
        List empty{};

        CHECK(empty.is_empty());
    }

    SECTION("clear") {
        List n{1,2,3,4,5,6,7,8,9,5,4,3,4,2,1,5,3,};

        n.clear();

        CHECK(n.is_empty());
    }

    SECTION("insert") {
        {
            List empty{};
            empty.insert(1);
            empty.insert(2);
            empty.insert(3);
            empty.insert(4);

            CHECK(empty.get_size() == 4);
            CHECK(empty.get_first()->get_data() == 1);
            CHECK(empty.get_last()->get_data() == 4);
        }

        {
            List empty{};
            empty.insert(4);
            empty.insert(3);
            empty.insert(2);
            empty.insert(1);

            CHECK(empty.get_size() == 4);
            CHECK(empty.get_first()->get_data() == 1);
            CHECK(empty.get_last()->get_data() == 4);
        }
        
        {
            List empty{};
            empty.insert(5);
            empty.insert(9);
            empty.insert(2);
            empty.insert(4);
            empty.insert(1);

            CHECK(empty.get_size() == 5);
            CHECK(empty.get_first()->get_data() == 1);
            CHECK(empty.get_last()->get_data() == 9);
        }

        {
            List empty{};
            empty.insert(5);
            empty.insert(9);
            empty.insert(2);
            empty.insert(2);
            empty.insert(2);
            empty.insert(4);
            empty.insert(4);
            empty.insert(1);

            CHECK(empty.get_size() == 8);
            CHECK(empty.get_first()->get_data() == 1);
            CHECK(empty.get_last()->get_data() == 9);
        }
    }

    SECTION("get") {
        {
            List l{1,2,3,4,5};

            CHECK(l.get(0).value() == 1);
            CHECK(l.get(1).value() == 2);
            CHECK(l.get(2).value() == 3);
            CHECK(l.get(3).value() == 4);
            CHECK(l.get(4).value() == 5);

            // Note that the None is converted to a bool, same as .value()
            CHECK_FALSE(l.get(55));
            CHECK_FALSE(l.get(44));
            CHECK_FALSE(l.get(5));
            CHECK_FALSE(l.get(-19));
            CHECK_FALSE(l.get(-1));
        }
    }

    SECTION("remove") {
        {
            List l{5};

            l.remove(0);
            
            CHECK(l.get_size() == 0);
            CHECK_FALSE(l.get(5));
        }
        {
            List l{1,2,3};

            l.remove(2);

            CHECK(l.get_size() == 2);
            CHECK(l.get_first()->get_data() == 1);
            CHECK(l.get_last()->get_data() == 2);
        }
        {
            stringstream ss;
            List l{0,1,2,3,4,5,6,7,8,9};

            l.remove(0);
            l.remove(5);
            l.remove(3);

            ss << l;
            CHECK(ss.str() == "1 2 3 5 7 8 9");
            CHECK(l.get_size() == 7);
            CHECK(l.get_first()->get_data() == 1);
            CHECK(l.get_last()->get_data() == 9);
        }
    }
}

TEST_CASE("Operators") {
    SECTION("Move") {
        stringstream ss1;
        stringstream ss2;
        List l1{1,2,3};
        List l2{4,5,6};

        l1 = move(l2);

        ss1 << l1;
        ss2 << l2;

        CHECK(ss1.str() == "4 5 6");
        CHECK(ss2.str() == "1 2 3");
    }
    
    SECTION("Copy") {
        stringstream ss1;
        stringstream ss2;
        List l1{1,2,3};
        List l2{4,5,6};

        l1 = l2;
        ss1 << l1;
        
        CHECK(ss1.str() == "4 5 6");

        // no matter what I do to l2, shouldn't change l1.

        l2.remove(0);
        l2.remove(1);

        ss2 << l1;

        CHECK(ss1.str() == "4 5 6");
        CHECK(l2.get_size() == 1);
    }
}

TEST_CASE("IO") {
    SECTION("<< output") {
        {
            stringstream ss;
            ss << List{1,2,3};
            CHECK(ss.str() == "1 2 3");
        }

        {
            stringstream ss;
            ss << List{5,9,2,4,1};
            CHECK(ss.str() == "1 2 4 5 9");
        }
    }
}

TEST_CASE("Iterator") {
    SECTION("Simple iteration") {
        stringstream ss;
        List l{2, 5, 7};
        for ( auto it = l.begin(); it != l.end(); ++it)
        {  
            ss << *it;
        }
        CHECK(ss.str() == "257");
    }
}