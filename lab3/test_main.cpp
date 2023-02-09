//#define CATCH_CONFIG_RUNNER
//#include "catch.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc <= 1) {
        cout << "input args" << endl;
        return 1;
    } else {
        for(int i = argc; i<argc; i++ ) {
            cout << argv[i] << endl;
        }

        cout << argc << endl;

        return 0;
    }
    //return Catch::Session{}.run(argc, argv);
}
