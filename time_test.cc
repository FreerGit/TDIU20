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


TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }

   SECTION("Integer")
   {
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

   SECTION("String")
   {
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

TEST_CASE ("is_am") 
{
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

TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   Time t5{1, 1, 1};
   Time t6{13, 9, 5};
   Time t7{13, 10, 10};

   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
      CHECK( t5.to_string() == "01:01:01" );
      CHECK( t6.to_string() == "13:09:05" );
      CHECK( t7.to_string() == "13:10:10" );
   }
   
   SECTION("24 hour format with argument")
   {
      // Fill with more tests!
   } 

   SECTION("12 hour format")
   {
      // Fill with more tests!
   }
}

// Fill with more tests of other functions and operators!


