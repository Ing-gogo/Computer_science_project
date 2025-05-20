#include <iostream>
#include <cmath>
#include <string>

using namespace std;
namespace Electronics// declares namespace for all electronics-based classes.
{
    const double PI = 3.141592653589793;
//Base class Component
    class Component {
    protected:
        double value; // resistance, capacitance, or inductance
    public:
        Component(double v) : value(v) {}// constructor
        virtual void printType() const = 0;// method to print type of the component
        virtual double reactance(double frequency) const = 0;// method used to calculate the reactance of components either inductive or capacitive reactance.
        virtual double powerLoss(double current) const = 0;// method to calculate power loss (only overriden in the Resistor class) 
        virtual ~Component() {}// destructor
    };
//Derived class Resistor 
    class Resistor : public Component {
    public:
        Resistor(double r) : Component(r) {}
        void printType() const override {
           cout << "Resistor\n";
        }
        double reactance(double) const override {
            return 0.0;
        }
        double powerLoss(double current) const override {
            return current * current * value;
        }
    };
//Derived class Capacitor
    class Capacitor : public Component {
    public:
        Capacitor(double c) : Component(c) {}
        void printType() const override {
            cout << "Capacitor\n";
        }
        double reactance(double frequency) const override {
            return 1.0 / (2 * PI * frequency * value);
        }
        double powerLoss(double) const override {
            return 0.0;//0.0 because no power is lost for a Capacitor
        }
    };
//Derived class Inductor
    class Inductor : public Component {
    public:
        Inductor(double l) : Component(l) {}
        void printType() const override {
            cout << "Inductor\n";
        }
        double reactance(double frequency) const override {
            return 2 * PI * frequency * value;
        }
        double powerLoss(double) const override {
            return 0.0;//0.0 because no power is lost on an inductor
        }
    };

} 
// main program
int main() {
    using namespace Electronics;// To bring in our classes
    int n;
    cout << "Enter the number of components: ";
    cin >> n;
//Loops through and prompts the user to input values for each component
    for (int i = 0; i < n; ++i) {
        string type;
        double value, frequency, current;
//Prompts user for component details
        cout << "\nComponent " << (i + 1) << " type (resistor/capacitor/inductor): ";
        cin >> type;

        cout << "Enter value (Ohms for resistor, Farads for capacitor, Henrys for inductor): ";
        cin >> value;

        cout << "Enter frequency (Hz): ";
        cin >> frequency;

        cout << "Enter current (Amps): ";
        cin >> current;
//Base class pointer for polymorphism
        Component* comp = nullptr;
//To determine which class to generate
        if (type == "resistor") {
            comp = new Resistor(value);
        } else if (type == "capacitor") {
            comp = new Capacitor(value);
        } else if (type == "inductor") {
            comp = new Inductor(value);
        } else {
            cout << "Invalid component type.\n";
            continue;
        }

//Displays results
        comp->printType();
        cout << "Reactance: " << comp->reactance(frequency) << " ohms\n";
        cout << "Power Loss: " << comp->powerLoss(current) << " watts\n";
        delete comp; // Free memory manually
    }
    return 0;
}

