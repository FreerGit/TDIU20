#include "catch.hpp"
#include "list.h"
#include <sstream>

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
}



TEST_CASE("IO") {
   SECTION("<< output") {
      {
         std::stringstream ss;
         ss << List{1,2,3};
         CHECK(ss.str() == "1 2 3");
      }

      {
         std::stringstream ss;
         ss << List{5,9,2,4,1};
         CHECK(ss.str() == "1 2 4 5 9");
      }
   }
}



