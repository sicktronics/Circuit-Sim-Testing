#include <vector>
#include "Component.h"
#pragma once

// Circuit class is where chained components are added and analysis is performed
// Start w DC OP analysis, don't worry about AC tran for now

class Circuit {
    std::vector<Component*> components;    // The netlist - a vector of circuit components
    std::vector<std::vector<double>> conductances; // NxN vector matrix
    std::vector<double> variables;                 // The variables vector
    std::vector<double> solutions;                 // The solutions vector
    std::vector<int> nodes;                        // Vector of nodes (each listed just once) in the circuit 
public:
    Circuit();                    // Constructor.
    virtual ~Circuit();           // Destructor.

    void addComponent(Component *compToAdd); // Adding a component to the netlist
    void dcOp(std::vector<Component*> compList); // Calculating all voltages and currents at each node
    // TO ADD:
    //  function for analysis of a circuit..
    //  void dcAnalysis() or summat
};