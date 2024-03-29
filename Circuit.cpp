#include "Circuit.h"

void Circuit::addComponent(Component *compToAdd){
    // Adding the new component to the components vector
    components.push_back(compToAdd);

    // Need to create a linked list, Where based on a components' output node, the component points to the corresponting comp
}

// This Modified Nodal Analysis works well for linear components (current source, res, voltage source). 
// But, when nonlinear devices are included, we will need to upgrade to Newton-Raphson for solving nonlinear SE.
void Circuit::dcOp(std::vector<Component*> compList){
    // Step 1: determine # of voltage variables, create voltage variable vector
    // IF a voltage source, append its current to the end of the voltage variable vector (i.e., I1)

    // Step 2: Create the current source vector by summing all current sources flowing into node i and subtracting all current sources flowing out of node i
    // IF a voltage source, append its voltage to the end of the current source vector

    // Then build the conductance matrix: NxN (with additional row/col added for each voltage source)
        // For element aii, add all conductances (1/R) directly attached to i
        // For element aij, add all conductances directly between i and j and multiply by -1
        // If voltage source:
            // add a 1 in the last column, in the row # corresponding to the node at which the voltage is impacted by the voltage source
            // add a 1 in the last row, in the column # associated with the node at which the voltage is impacted.

    // Finally, solve this matrix to get voltages at each node


}