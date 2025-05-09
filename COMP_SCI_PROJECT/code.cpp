#include <iostream>
#include <cmath>
#include <vector>
#include <memory> // For smart pointers

namespace Electronics {

    const double PI = 3.141592653589793;

    class Component {
    protected:
        double value; // resistance, capacitance, or inductance
    public:
        Component(double v) : value(v) {}
        virtual void printType() const = 0;
        virtual double reactance(double frequency) const = 0;
        virtual double powerLoss(double current) const = 0;
        virtual ~Component() {}
    };

    class Resistor : public Component {
    public:
        Resistor(double r) : Component(r) {}
        void printType() const override {
            std::cout << "Resistor\n";
        }
        double reactance(double) const override {
            return 0.0;
        }
        double powerLoss(double current) const override {
            return current * current * value;
        }
    };

    class Capacitor : public Component {
    public:
        Capacitor(double c) : Component(c) {}
        void printType() const override {
            std::cout << "Capacitor\n";
        }
        double reactance(double frequency) const override {
            return 1.0 / (2 * PI * frequency * value);
        }
        double powerLoss(double) const override {
            return 0.0;
        }
    };

    class Inductor : public Component {
    public:
        Inductor(double l) : Component(l) {}
        void printType() const override {
            std::cout << "Inductor\n";
        }
        double reactance(double frequency) const override {
            return 2 * PI * frequency * value;
        }
        double powerLoss(double) const override {
            return 0.0;
        }
    };

} // namespace Electronics

int main() {
    using namespace Electronics;
    using namespace std;

    vector<unique_ptr<Component>> components;

    int n;
    cout << "Enter the number of components: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string type;
        double value, frequency, current;

        cout << "\nComponent " << (i + 1) << " type (resistor/capacitor/inductor): ";
        cin >> type;

        cout << "Enter value (Ohms for resistor, Farads for capacitor, Henrys for inductor): ";
        cin >> value;

        cout << "Enter frequency (Hz): ";
        cin >> frequency;

        cout << "Enter current (Amps): ";
        cin >> current;

        Component* comp = nullptr;

        if (type == "resistor") {
            comp = new Resistor(value);
        } else if (type == "capacitor") {
            comp = new Capacitor(value);
        } else if (type == "inductor") {
            comp = new Inductor(value);
        } else {
            cout << "Invalid component type. Skipping...\n";
            continue;
        }

        components.emplace_back(comp);

        comp->printType();
        cout << "Reactance: " << comp->reactance(frequency) << " ohms\n";
        cout << "Power Loss: " << comp->powerLoss(current) << " watts\n";
    }

    return 0;
}

