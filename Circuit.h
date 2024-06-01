#include <vector>
#include "Component.h"
#include "Res_5p_Tol.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#pragma once

// Gooood morning!!! <3 4/27/24

/*
* To understand the theory behind the code, check out this tutorial series (up to DC Op): https://www.youtube.com/watch?v=1ZhzhWAt7xc
*/

/*
* The Circuit struct (public members by default)
* is home to the actual vector that represents the
* circuit. Has methods for performing analysis.
*/
struct Circuit {

    std::vector<std::vector<double> > conductances; // NxN conductance vector matrix
    std::vector<Component*> components;             // The netlist - a vector of circuit components

    std::vector<Res_5p_Tol*> resistors;             // A vector of just the resistors in the ckt
    std::vector<VoltageSource*> vSrcs;              // A vector of just the voltage srcs in the ckt
    std::vector<CurrentSource*> cSrcs;              // A vector of just the current srcs in the ckt

    int numVS = 0;              // # of voltage sources
    int numCS = 0;              // # of current sources
    int condMatrixDim;          // dimensions of conductance matrix (impacted by voltage sources)
    int numCondNodes;           // number of nodes to which resistors are attached 
                                // (i.e. are added to the conductance matrix)

    // Constructor with some default initializations
    Circuit(){numVS = 0; numCondNodes = 0;};

    void addComponent(Component *compToAdd); // Adding a component to the netlist
    void dcOp(); // Calculating all voltages and currents at each node (DC)
};