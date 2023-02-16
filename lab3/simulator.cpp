#include "simulator.h"
#include <iostream>
#include <iomanip>

using namespace std;

Component::Component(string const& n, Connection& l, Connection& r) : name{n}, left{l}, right{r}
{}

double Component::get_voltage() const {
    return abs(this->left - this->right);
}

double Component::get_current() const {
    return 0.0;
}

string Component::get_name() const {
    return this->name;
}

Battery::Battery(string const& n, double v, Connection& l, Connection& r) : Component{n,l,r}, voltage{v}
{}

double Battery::get_current() const {
    return 0.0;
}

void Battery::calculate(double time) {
    double to_disable_param_unused_warning = time * 0.0;
    this->left = this->voltage;
    this->right = to_disable_param_unused_warning;
}

Resistor::Resistor(std::string const& n, double res, Connection& l, Connection& r)
    : Component{n,l,r}, resistance{res}
{}

double Resistor::get_current() const {
    return (this->get_voltage() / this->resistance);
}

void Resistor::calculate(double time) {
    double smth{this->get_current() * time};
    if (this->left > this->right) {
        this->left -= smth;
        this->right += smth;
    } else {
        this->left += smth;
        this->right -= smth;
    }
}   

Condensator::Condensator(string const& n, double cap, Connection& l, Connection& r) 
    : Component{n,l,r}, capacitance{cap}, charge{0.0}
{}

double Condensator::get_current() const {
    return (this->capacitance * (this->get_voltage() - this->charge));
}

void Condensator::calculate(double time) {
    double smth{this->get_current() * time};
    this->charge += smth;
    if(this->left > this->right) {
        this->left -= smth;
        this->right += smth;
    } else {
        this->left += smth;
        this->right -= smth;
    }
}

void simulate(vector<Component*> comps, int iterations, int rows, double time) {
    for(unsigned int i{0}; i < comps.size(); i++) {
        if(i == 0) {
            cout << "        ";
        } else {
            cout << "          ";
        }
        cout << comps[i]->get_name();
    }
    cout << endl;

    cout << " ";
    for(unsigned int i{0}; i < comps.size(); i++) {
        cout << "Volt" << "  " << "Curr";
        if( i != comps.size() -1) {
            cout << "  ";
        }
    }
    cout << endl;

    for(int i{1}; i < iterations+1; i++) {
        for(auto c : comps) {
            c->calculate(time);
        }

        if(i % (iterations/rows) == 0) {
            for(auto c : comps) {
                cout << setprecision(2) << fixed << c->get_voltage() << "  " << c->get_current() << "  ";
            }
            cout << endl;
        }
    }
}