#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include <vector>

using Connection = double;

class Component {
public:
    Component(std::string const& n, Connection& l, Connection& r);
    virtual ~Component() = default;
    double get_voltage() const;
    std::string get_name() const;
    virtual double get_current() const = 0;
    virtual void calculate(double) = 0;


protected: 
    std::string name;
    Connection& left;
    Connection& right;
};

class Battery : public Component {
public:
    Battery(std::string const& n, double v, Connection& l, Connection& r);
    double get_current() const override;
    void calculate(double time) override;

private:
    double voltage;
};

class Resistor : public Component {
public:
    Resistor(std::string const& n, double res, Connection& l, Connection& r);
    double get_current() const override;
    void calculate(double time) override;

private:
    double resistance;
};

class Condensator : public Component {
public:
    Condensator(std::string const& n, double cap, Connection& l, Connection& r);
    double get_current() const override;
    void calculate(double time) override;
private:
    double capacitance;
    double charge;
};


void simulate(std::vector<Component*>& comps, int iterations, int rows, double time);

void cleanup(std::vector<Component*>& comps);

#endif