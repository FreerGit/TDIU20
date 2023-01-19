#include "catch.hpp"
#include "Time.h"

using namespace std;

// LÄS FÖRST HELA VÄGEN TILL RAD 65. LÄS NOGA.

// I denna fil skriver ni alla testfall huvudprogrammet ska köra.
// Huvudprogrammet finns test_main.cc så det kan kompileras för sig en gång för alla.

// Ni ska arbeta med uppgiften enligt TDD (Test Driven Developement)
// Snabbintroduktion till TDD:
//  1. Lägg till ett testfall.
//  2. Gör minsta möjliga otillräckliga stub-implementation så att testfallet kompilerar.
//  3. Kör testprogrammet.
//     Du ska se att testfallet detekterar otillräcklig implementation (misslyckas).
//  4. Lägg till (minsta möjliga) korrekta implementation.
//  5. Kör testprogrammet med alla testfall.
//     Du ska se att alla testfall, tidigare och det nya, går igenom.
//  6. Refaktorera (skriv om) så att koden ser bra ut
//  7. Kör testprogrammet med alla testfall.
//     Du ska se att alla testfall, tidigare och det nya, fortfarande går igenom.

// Catch är ett ramverk som hjälper till med all logik för att gå
// igenom alla testfall, köra dem, visa tester som misslyckas, och
// sammanställa resultatet.

// Ni ska använda catch när ni skriver testfallen.
// Full dokumentation:
// https://github.com/catchorg/Catch2/tree/devel/docs#reference

// Snabbintroduktion till Catch:


TEST_CASE ("Constructors and getters") {
   SECTION("Default constructor") {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Constructor with args") {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }

   SECTION("Constructor with string") {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }
}

TEST_CASE ("is_am") {
   Time t0{"00:00:00"};
   Time t1{"05:00:00"};
   Time t2{"11:59:59"};
   Time t3{"12:00:00"};
   Time t4{"14:00:00"};
   Time t5{"23:59:59"};

   CHECK       ( t0.is_am() );
   CHECK       ( t1.is_am() );
   CHECK       ( t2.is_am() );
   CHECK_FALSE ( t3.is_am() );
   CHECK_FALSE ( t4.is_am() );
   CHECK_FALSE ( t5.is_am() );
}

TEST_CASE ("to_string") {
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   Time t5{1, 1, 1};
   Time t6{13, 9, 5};
   Time t7{13, 10, 10};

   SECTION("24 hour format no argument") {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
      CHECK( t5.to_string() == "01:01:01" );
      CHECK( t6.to_string() == "13:09:05" );
      CHECK( t7.to_string() == "13:10:10" );
   }
   
   SECTION("24 hour format with argument") {
      Time t0{12,0,0};
      CHECK( t0.to_string(false) == "12:00:00" );
   } 

   SECTION("12 hour format") {
      Time t0{};
      Time t1{0,0,0};
      Time t2{0,0,1};
      Time t3{1,0,0};
      Time t4{11,0,0};
      Time t5{11,59,59};
      Time t6{12,0,0};
      Time t7{12,1,0};
      Time t8{13,0,0};
      Time t9{23,0,0};
      Time t10{23,59,59};

      CHECK( t0.to_string(true) == "12:00:00am" );
      CHECK( t1.to_string(true) == "12:00:00am" );
      CHECK( t2.to_string(true) == "12:00:01am" );
      CHECK( t3.to_string(true) == "01:00:00am" );
      CHECK( t4.to_string(true) == "11:00:00am" );
      CHECK( t5.to_string(true) == "11:59:59am" );
      CHECK( t6.to_string(true) == "12:00:00pm" );
      CHECK( t7.to_string(true) == "12:01:00pm" );
      CHECK( t8.to_string(true) == "01:00:00pm" );
      CHECK( t9.to_string(true) == "11:00:00pm" );
      CHECK( t10.to_string(true) == "11:59:59pm" );
   }
}

TEST_CASE ("CPP standard operators") {
   SECTION("Addition") {
      Time t0{};
      Time t1{12,0,59};
      Time t2{12,59,59};
      Time t3{23,59,59};

      CHECK( (t0 + 1).get_second() == 1 );
      CHECK( (t0 + 1).get_minute() == 0 );

      CHECK( (t0 + 19).get_second() == 19);

      CHECK( (t1 + 1).get_second() == 0);
      CHECK( (t1 + 1).get_minute() == 1);

      CHECK( (t2 + 1).get_second() == 0);
      CHECK( (t2 + 1).get_minute() == 0);
      CHECK( (t2 + 1).get_hour() == 13);

      CHECK( (t3 + 1).get_second() == 0);
      CHECK( (t3 + 1).get_minute() == 0);
      CHECK( (t3 + 1).get_hour() == 0);
   }

   SECTION("Subtraction") {
      Time t0{0,0,1};
      Time t1{12,01,0};
      Time t2{12,0,0};
      Time t3{12,12,12};
      Time t4{};

      CHECK( (t0 - 1).get_second() == 0 );
      CHECK( (t0 - 1).get_minute() == 0 );

      CHECK( (t1 - 1).get_second() == 59);
      CHECK( (t1 - 1).get_minute() == 0);

      CHECK( (t2 - 1).get_second() == 59);
      CHECK( (t2 - 1).get_minute() == 59);
      CHECK( (t2 - 1).get_hour() == 11);

      CHECK( (t3 - 11).get_second() == 1);
      CHECK( (t3 - 11).get_minute() == 12);
      CHECK( (t3 - 11).get_hour() == 12);

      CHECK( (t4 - 1).get_second() == 59);
      CHECK( (t4 - 1).get_minute() == 59);
      CHECK( (t4 - 1).get_hour() == 23);
   }

   SECTION("Post increment") {
      Time t0{};

      CHECK( t0++.to_string() == "00:00:00");
      CHECK( t0.to_string() == "00:00:01");
   }

   SECTION("Pre increment") {
      Time t0{};

      CHECK( (++t0).to_string() == "00:00:01");
      CHECK( t0.to_string() == "00:00:01");
   }

   SECTION("Post decrement") {
      Time t0{};

      CHECK( t0--.to_string() == "00:00:00");
      CHECK( t0.to_string() == "23:59:59");
   }

   SECTION("Pre decrement") {
      Time t0{};

      CHECK( (--t0).to_string() == "23:59:59");
      CHECK( t0.to_string() == "23:59:59");
   }
}

// Fill with more tests of other functions and operators!


