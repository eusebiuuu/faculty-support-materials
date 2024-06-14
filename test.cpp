#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        std::cout << "Base constructor" << std::endl;
        // Virtual function call
        print();
    }
    virtual void print() const {
        std::cout << "Base print" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor" << std::endl;
        print();
    }
    void print() const {
        std::cout << "Derived print" << std::endl;
    }
};

int main() {
    Derived d;
    return 0;
}