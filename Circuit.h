#include <vector>
#include "Component.h"
#include "Res_5p_Tol.h"
#pragma once

// Circuit class is where chained components are added and analysis is performed
// Start w DC OP analysis, don't worry about AC tran for now

struct Circuit {
    std::vector<std::vector<double> > conductances; // NxN conductance vector matrix
    std::vector<double> variables;                 // The variables vector
    std::vector<double> solutions;                 // The solutions vector

    // std::vector<int> visitedInNodes;               // Vector of visited input nodes

    std::vector<Component*> components;    // The netlist - a vector of circuit components

    std::vector<Res_5p_Tol*> resistors;

    int numVS;              // # of voltage sources
    int condMatrixDim;      // dimensions of conductance matrix (impacted by voltage sources)

    int numCondNodes;       // number of nodes to which resistors are attached (i.e. are attached to the conductance matrix)

    Circuit(){numVS = 0; numCondNodes = 0;};

    void addComponent(Component *compToAdd); // Adding a component to the netlist
    void dcOp(); // Calculating all voltages and currents at each node
    // int getCompLen();
    // TO ADD:
    //  function for analysis of a circuit..
    //  void dcAnalysis() or summat
};