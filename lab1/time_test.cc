#include "catch.hpp"
#include "Time.h"
#include <iostream>
#include <sstream>

using namespace std;

/*

// Information om komplettering:
// Siffrorna hänvisar till rättningsprotokollet som finns på
// kurshemsidan -> läsning -> Literatur -> "Uppgruppens bedömningsprotokoll"
// Kompletteringen kan gälla hela filen och alla filer i labben,
// så får ni komplettering på en sak, kan samma sak förekomma på
// fler ställen utan att jag skrivit det.
//
// Komplettering lämnas in via sendlab efter senast en (1) vecka
//
// Har ni frågor om kompletteringen kan ni maila mig på:
// nadim.lakrouz@liu.se

// DONE
// Komplettering: Operatorer och funktioner som inte ändrar på objektets tillstånd ska markeras// som konstanta.
// Komplettering: hjälpfunktioner ska deklareras som private. 
// Komplettering: operator+ för kommutativa fallet saknas.
// Komplettering: En testfil ska pröva de funktioner som
// ni har skapat. Det innebär att man vill pröva alla
// möjliga fall (även specialfall). Vi vill ju vara säkra
// på att vi har en funktion som fungerar. En bra fråga är:
// "Övertygar detta den som rättar att er funktion
// fungerar utan att kolla i Time.cc-filen?"
  
*/

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
      CHECK_THROWS( Time{23,0,-1} );
      CHECK_THROWS( Time{23,-5,0} );
      CHECK_THROWS( Time{-55,55,0} );
             
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
      CHECK_THROWS( Time{"fdasfdsafdsa"} );
      CHECK_THROWS( Time{"23:11:aa"} );
      CHECK_THROWS( Time{"23:bb:11"} );
      CHECK_THROWS( Time{"aa:55:22"} );
      CHECK_THROWS( Time{"321321321321321"} );
      CHECK_THROWS( Time{"22:55:4a"} );
      CHECK_THROWS( Time{"22:55:22:::"} );

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
      Time t0{5,0,0};
      Time t1{12,0,0};
      Time t2{20,0,0};
      CHECK( t0.to_string(false) == "05:00:00" );
      CHECK( t1.to_string(false) == "12:00:00" );
      CHECK( t2.to_string(false) == "20:00:00" );
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
      Time t11{"23:59:59"};


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
      CHECK( t11.to_string(true) == "11:59:59pm" );
   }
}

TEST_CASE ("CPP standard operators") {
   SECTION("Addition") {
      Time t0{};
      Time t1{12,0,59};
      Time t2{12,59,59};
      Time t3{23,59,59};

      CHECK(t3 + 1 == 1 + t3);
      CHECK(t3 + 999 == 999 + t3);

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


      CHECK( (t0 + 120).get_second() == 0);
      CHECK( (t0 + 120).get_minute() == 2);
      CHECK( (t0 + 120).get_hour() == 0);

      CHECK( (t0 + 3600).get_second() == 0);
      CHECK( (t0 + 3600).get_minute() == 0);
      CHECK( (t0 + 3600).get_hour() == 1);

      CHECK( (t0 + 180000).get_second() == 0);
      CHECK( (t0 + 180000).get_minute() == 0);
      CHECK( (t0 + 180000).get_hour() == 2);

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

      CHECK( (t4 - 120).get_second() == 0);
      CHECK( (t4 - 120).get_minute() == 58);
      CHECK( (t4 - 120).get_hour() == 23);
   
      CHECK( (t4 - 3600).get_second() == 0);
      CHECK( (t4 - 3600).get_minute() == 0);
      CHECK( (t4 - 3600).get_hour() == 23);

      CHECK( (t4 - 180000).get_second() == 0);
      CHECK( (t4 - 180000).get_minute() == 0);
      CHECK( (t4 - 180000).get_hour() == 22);
   }

   SECTION("Post increment") {
      Time t0{};
      Time t1{20,59,59};
      Time t2{22,50,59};
      Time t3{23,59,59};

      CHECK( t0++.to_string() == "00:00:00");
      CHECK( t0.to_string() == "00:00:01");
      CHECK( t1++.to_string() == "20:59:59");
      CHECK( t1.to_string() == "21:00:00");
      CHECK( t2++.to_string() == "22:50:59");
      CHECK( t2.to_string() == "22:51:00");
      CHECK( t3++.to_string() == "23:59:59");
      CHECK( t3.to_string() == "00:00:00");
   }

   SECTION("Pre increment") {
      Time t0{};
      Time t1{21,50,59};
      Time t2{23,59,59};

      CHECK( (++t0).to_string() == "00:00:01");
      CHECK( t0.to_string() == "00:00:01");
      CHECK( (++t1).to_string() ==  "21:51:00");
      CHECK( t1.to_string() == "21:51:00");
      CHECK( (++t2).to_string() ==  "00:00:00");
      CHECK( t2.to_string() == "00:00:00");
   }

   SECTION("Post decrement") {
      Time t0{};
      Time t1{21, 00, 00};
      Time t2{20,50,00};

      CHECK( t0--.to_string() == "00:00:00");
      CHECK( t0.to_string() == "23:59:59");
      CHECK( t1--.to_string() == "21:00:00");
      CHECK( t1.to_string() == "20:59:59");      
      CHECK( t2--.to_string() == "20:50:00");
      CHECK( t2.to_string() == "20:49:59");
   }

   SECTION("Pre decrement") {
      Time t0{};
      Time t1{21, 00, 00};
      Time t2{20,50,00};

      CHECK( (--t0).to_string() == "23:59:59");
      CHECK( t0.to_string() == "23:59:59");
      CHECK( (--t1).to_string() == "20:59:59");
      CHECK( t1.to_string() == "20:59:59");      
      CHECK( (--t2).to_string() == "20:49:59");
      CHECK( t2.to_string() == "20:49:59");
   }

   SECTION("<") {
      Time t0{};
      Time t1{12,0,0};
   
      CHECK       ( (t0 < t1));
      CHECK_FALSE ( (t1 < t0) );
      CHECK_FALSE ( (t0 < t0) );
      CHECK_FALSE ( (t1 < t1) );
   }

   SECTION("==") {
      Time t0{};
      Time t1{12,0,0};

      CHECK       ( (t0 == t0));
      CHECK       ( (t1 == t1));
      CHECK       ( (t0 == Time{}));
      CHECK_FALSE ( (t1 == t0));
      CHECK_FALSE ( (t0 == t1));
   }

   SECTION(">") {
      Time t0{};
      Time t1{12,0,0};
   
      CHECK       ( (t1 > t0));
      CHECK_FALSE ( (t0 > t1) );
      CHECK_FALSE ( (t0 > t0) );
      CHECK_FALSE ( (t1 > t1) );
   }

   SECTION("!=") {
      Time t0{};
      Time t1{12,0,0};

      CHECK       ( (t0 != t1));
      CHECK       ( (t1 != t0));
      CHECK       ( (t1 != Time{}));
      CHECK_FALSE ( (t0 != Time{}));
      CHECK_FALSE ( (t0 != t0));
      CHECK_FALSE ( (t1 != t1));
   }

   SECTION("<=") {
      Time t0{};
      Time t1{12,0,0};

      CHECK       ( (t0 <= t0));
      CHECK       ( (t1 <= t1));
      CHECK       ( (t0 <= t1));
      CHECK_FALSE ( (t1 <= Time{}));
      CHECK_FALSE ( (t1 <= t0));
   }

   SECTION(">=") {
      Time t0{};
      Time t1{12,0,0};

      CHECK       ( (t0 >= t0));
      CHECK       ( (t1 >= t0));
      CHECK       ( (t1 >= t1));
      CHECK       ( (t1 >= Time{}));
      CHECK_FALSE ( (t0 >= t1));
      CHECK_FALSE ( (t0 >= Time{1,0,0}));
   }
}

TEST_CASE("IO") {
   SECTION("<< output") {
      {
         std::stringstream ss;
         ss << Time{0,0,0};
         CHECK(ss.str() == "00:00:00");
      }

      {
         std::stringstream ss;
         ss << Time{};
         CHECK(ss.str() == "00:00:00");
      }

      {
         std::stringstream ss;
         ss << Time{12,59,59};
         CHECK(ss.str() == "12:59:59");
      }

      {
         std::stringstream ss;
         ss << Time{13,0,0};
         CHECK(ss.str() == "13:00:00");
      }

      {
         std::stringstream ss;
         ss << Time{13,0,0} << "text";
         CHECK(ss.str() == "13:00:00text");
      }
   }

   SECTION(">> input") {
      {
         std::string s{"00:00:00"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(t == Time{});
      }

      {
         std::string s{"12:00:00"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(t == Time{12,0,0});
      }

      {
         std::string s{"23:59:21"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(t == Time{23,59,21});
      }

      {
         std::string s{"50:00:00"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(ss.failbit);
         CHECK(t == Time{}); // default;
      }

      {
         std::string s{"a1:55:55"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(ss.failbit);
         CHECK(t == Time{}); // default;
      }

      {
         std::string s{"21:bb:55"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(ss.failbit);
         CHECK(t == Time{}); // default;
      }

      {
         std::string s{"21:55:"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(ss.failbit);
         CHECK(t == Time{}); // default;
      }

      {
         std::string s{"21::22"};
         std::stringstream ss{s};
         Time t{};
         ss >> t;
         CHECK(ss.failbit);
         CHECK(t == Time{}); // default;
      }
   }
}


