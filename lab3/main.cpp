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

    Connection a{}, b{}, c{}, d{};
    vector<Component*> nets1;
    vector<Component*> nets2;
    vector<Component*> nets3;

    cout << "Krets 1:" << endl;
    nets1.push_back(new Battery("Bat", voltage, a, b));
    nets1.push_back(new Resistor("R1", 6.0, a, c));
    nets1.push_back(new Resistor("R2", 4.0, c, d));
    nets1.push_back(new Resistor("R3", 8.0, d, b));
    nets1.push_back(new Resistor("R4", 12.0, c, b));
    simulate(nets1, iterations, rows, time);

    cout << endl << "Krets 2:" << endl;
    Connection p{}, n{}, l{}, r{};
    nets2.push_back(new Battery("Bat", voltage, p, n));
    nets2.push_back(new Resistor("R1", 150.0, p, l));
    nets2.push_back(new Resistor("R2", 50.0, p, r));
    nets2.push_back(new Resistor("R3", 100.0, l, r));
    nets2.push_back(new Resistor("R4", 300.0, l, n));
    nets2.push_back(new Resistor("R5", 250.0, n, r));
    simulate(nets2, iterations, rows, time);

    cout << endl << "Krets 3:" << endl;
    Connection p2{}, n2{}, l2{}, r2{};
    nets3.push_back(new Battery("Bat", voltage, p2, n2));
    nets3.push_back(new Resistor("R1", 150.0, p2, l2));
    nets3.push_back(new Resistor("R2", 50.0, p2, r2));
    nets3.push_back(new Condensator("C3", 1.0, l2, r2));
    nets3.push_back(new Resistor("R4", 300.0, l2, n2));
    nets3.push_back(new Condensator("C5", 0.75, n2, r2));
    simulate(nets3, iterations, rows, time);
}