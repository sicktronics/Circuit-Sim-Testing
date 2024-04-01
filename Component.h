#include <vector>
#pragma once

// Base Component - ins from https://electronics.stackexchange.com/questions/239532/how-does-spice-parse-a-netlist
class Component {
    std::vector<int> inputs;    // Vector of input nodes
    std::vector<int> outputs;   // Vector of output nodes
public:
    Component();                    // Constructor.
    virtual ~Component();           // Destructor.
    int compID;

    virtual void addInput(int n);   // Function for adding an input node
    virtual void addOutput(int n);  // Function for adding an output node

    // virtual method for checking component id
    virtual int returnCompID();
};
