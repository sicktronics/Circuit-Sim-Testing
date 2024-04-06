#include <vector>
#include "Component.h"
#pragma once

// Circuit class is where chained components are added and analysis is performed
// Start w DC OP analysis, don't worry about AC tran for now

class Circuit {
    std::vector<std::vector<double>> conductances; // NxN conductance vector matrix
    std::vector<double> variables;                 // The variables vector
    std::vector<double> solutions;                 // The solutions vector
    std::vector<int> visitedInNodes;               // Vector of visited input nodes
public:
    // Circuit();                    // Constructor.
    // virtual ~Circuit();           // Destructor.

    std::vector<Component*> components;    // The netlist - a vector of circuit components

    void addComponent(Component *compToAdd); // Adding a component to the netlist
    void dcOp(std::vector<Component*> compList); // Calculating all voltages and currents at each node
    // int getCompLen();
    // TO ADD:
    //  function for analysis of a circuit..
    //  void dcAnalysis() or summat
};