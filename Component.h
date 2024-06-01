#include <vector>
#pragma once

/*
* Parent class for linear components
* Contains:
* - function for adding an input node
* - function for adding an output node
* inspo from https://electronics.stackexchange.com/questions/239532/how-does-spice-parse-a-netlist
*/
struct Component {
    std::vector<int> inputs;    // Vector of input nodes
    std::vector<int> outputs;   // Vector of output nodes
    int compID;                 // Unique ID for component type

    Component(){};          // Constructor.
    void addInput(int n);   // Function for adding an input node
    void addOutput(int n);  // Function for adding an output node
};
