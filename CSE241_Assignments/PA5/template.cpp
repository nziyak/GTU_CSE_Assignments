#include <iostream>
#include <vector>
#include <string>

// Base class for A
class ABase {
public:
    virtual ~ABase() = default;
    virtual void printValue() const = 0;
};

// Template class A inheriting from ABase
template<typename T>
class A : public ABase {
private:
    T value;

public:
    A(T val) : value(val) {}

    void printValue() const override {
        std::cout << value << std::endl;
    }
};

// Class B that contains a 2D vector of ABase pointers
class B {
private:
    std::vector<std::vector<ABase*>> aVector;

public:
    ~B() {
        // Destructor to clean up allocated memory using regular for loops
        for (size_t i = 0; i < aVector.size(); ++i) {
            for (size_t j = 0; j < aVector[i].size(); ++j) {
                delete aVector[i][j];
            }
        }
    }

    void addRow() {
        aVector.emplace_back(); // Add a new row
    }

    template<typename T>
    void addElement(int row, T val) {
        if (row >= 0 && row < aVector.size()) {
            aVector[row].push_back(new A<T>(val));
        } else {
            std::cerr << "Invalid row index" << std::endl;
        }
    }

    void printElements() const {
        for (const auto& row : aVector) {
            for (const auto& elem : row) {
                elem->printValue();
            }
            std::cout << "-----" << std::endl; // Row separator
        }
    }
};

int main() {
    B b;

    // Add two rows
    b.addRow();
    b.addRow();

    // Add elements to the first row
    b.addElement(0, 10);                   // Adding an int to the first row
    b.addElement(0, 20.5);                 // Adding a double to the first row
    b.addElement(0, std::string("Hello")); // Adding a string to the first row

    // Add elements to the second row
    b.addElement(1, 30);                   // Adding an int to the second row
    b.addElement(1, 40.5);                 // Adding a double to the second row
    b.addElement(1, std::string("World")); // Adding a string to the second row

    std::cout << "Elements in B:" << std::endl;
    b.printElements();

    return 0;
}
