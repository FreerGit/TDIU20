#include "simulator.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    int iterations, rows, voltage;
    double time;
    if(argc == 5) {
        try {
            iterations = stoi(argv[1]);
            rows = stoi(argv[2]);
            time = stod(argv[3]);
            voltage = stoi(argv[4]);
        } catch (invalid_argument &e) {
            cerr << e.what() << endl;
            exit(0);
        }

        if (iterations <= 0 || rows <= 0 || time <= 0 || voltage <= 0) {
            cerr << "Out of range" << endl;
            return 1;
        }
    } else {
        cerr << "Invalid inputs (./a.out iterations rows time volt)" << endl;
        return 1;
    }

    Connection a{},b{},c{},d{};
    vector<Component*> nets;

    nets.push_back(new Battery("Bat", voltage, a, b));
    nets.push_back(new Resistor("R1", 6.0, a, c));
    nets.push_back(new Resistor("R2", 4.0, c, d));
    nets.push_back(new Resistor("R3", 8.0, d, b));
    nets.push_back(new Resistor("R4", 12.0, c, b));
    simulate(nets, iterations, rows, time);
}