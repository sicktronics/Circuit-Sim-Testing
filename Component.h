#include <vector>
#pragma once

// *** If an input/output is "0", it is treated as GND ***


// Base Component - ins from https://electronics.stackexchange.com/questions/239532/how-does-spice-parse-a-netlist
struct Component {
    std::vector<int> inputs;    // Vector of input nodes
    std::vector<int> outputs;   // Vector of output nodes
    int compID;

    Component(){};                // Constructor.
    void addInput(int n);   // Function for adding an input node
    void addOutput(int n);  // Function for adding an output node

    // virtual method for checking component id
    // int returnCompID();
};
