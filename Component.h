#include <vector>
#pragma once

// Base Component - ins from https://electronics.stackexchange.com/questions/239532/how-does-spice-parse-a-netlist
struct Component {
    std::vector<int> inputs;    // Vector of input nodes
    std::vector<int> outputs;   // Vector of output nodes
    int compID;

    Component(){};                // Constructor.
    // virtual ~Component();       // Destructor.

    // LEARN MORE ABOUT VIRTUAL. IT IS CAUSING ISSUES
    // RESOURCES: https://stackoverflow.com/questions/31861803/a-missing-vtable-usually-means-the-first-non-inline-virtual-member-function-has
    // https://www.simplilearn.com/tutorials/cpp-tutorial/virtual-function-in-cpp
    // Virtual functions MUST be defined in the base class
    void addInput(int n);   // Function for adding an input node
    void addOutput(int n);  // Function for adding an output node

    // virtual method for checking component id
    // int returnCompID();
};
