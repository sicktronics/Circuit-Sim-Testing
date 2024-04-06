#include "Circuit.h"
#include <iostream>

// Complexity: O(n)
void Circuit::addComponent(Component *compToAdd){
    // Check if voltage source:
    if(compToAdd->compID==1){
        numVS++;
    }
    // Adding the new component to the components vector
    // STEP 1 - SORT 
    // IF components size is 0, (aka first element) add to list
    if(components.size() < 1 || resistors.size() < 1){
        components.push_back(compToAdd);

        // Add to RES
        if(compToAdd->compID==0){
            resistors.push_back((Res_5p_Tol*)compToAdd);
        }
    }

    // TO DO: ADD CHECK TO MAKE SURE COMPONENT HAS BEEN INITIALIZED WITH AN INPUT AND OUTPUT NODE

    else{
        // FOR COND MATRIX
        if(compToAdd->compID==0){
            for(int i = resistors.size() - 1; i >= 0 ; i--){
                // Add to RES
                if(compToAdd->inputs[0] >= resistors[i]->inputs[0]){
                    resistors.insert(resistors.begin() + (i+1), (Res_5p_Tol*)compToAdd);
                    break;
                }
            }                
        }
        for(int i = components.size() - 1; i >=0 ; i--){
            if(compToAdd->inputs[0] >= components[i]->inputs[0]){ 
                // add the component to the next spot
                components.insert(components.begin() + (i+1), compToAdd);
                break;
            }
        }
    }
}

// This Modified Nodal Analysis works well for linear components (current source, res, voltage source). 
// But, when nonlinear devices are included, we will need to upgrade to Newton-Raphson for solving nonlinear SE.
void Circuit::dcOp(){

    // STEP 0: Need to track number of nodes in the matrix
    // --Number of resistor nodes--
    for (int i = 0; i < resistors.size(); i++) {
        // Move the index ahead while
        // there are duplicates
        while (i < (resistors.size() - 1) && resistors[i]->inputs[0] == resistors[i + 1]->inputs[0]){
            i++;
        }
        numCondNodes++;
    }
    std::cout << "number of cond nodes: " << numCondNodes << std::endl;

    // Step 1: determine # of voltage variables, create voltage variable vector
    // IF a voltage source, append its current to the end of the voltage variable vector (i.e., I1)

    // Step 2: Create the current source vector by summing all current sources flowing into node i and subtracting all current sources flowing out of node i
    // IF a voltage source, append its voltage to the end of the current source vector

    // Then build the conductance matrix: NxN (with additional row/col added for each voltage source)

    // TO DO : TRACK DISTINCT NODES
    condMatrixDim = numCondNodes + numVS;

    // THE CONDUCTANCE MATRIX
    double condMatrix[condMatrixDim][condMatrixDim];


/* - - - - - 
 ~Rules of the game ~
 row, col (i, j) corresponds to node (i+1, j+1)
 TO DO : MAKE THIS MORE ROBUST
- - - - - */ 


    double nodeCondDiag;
    double nodeCondNonDiag;

    // For each row...
    for(int i = 0; i < condMatrixDim; i++){
        // And each column...
        for (int j = 0; j < condMatrixDim; j++)
        {
            // For element aii, add all conductances (1/R) directly attached to i
            if(i==j){
                // iterate over resistors.
                // then add sum of conductances to a_ii
                for(int index = 0; index < resistors.size(); index++){
                    // If input node OR output node is (i+1)
                    if(resistors[index]->inputs[0] == (i+1) || resistors[index]->outputs[0] == (i+1)){ // i+1 so that 0,0 on matrix is populated by node 1, 1,1 by node 2, etc
                        
                        // Add its conductance (1/R) to the nodeCond 
                        nodeCondDiag += (1/resistors[index]->ohm);
                    }
                }

                condMatrix[i][j] = nodeCondDiag;
                nodeCondDiag = 0;

            }

            // For element aij, add all conductances directly between i and j and multiply by -1
            else if(i != j){
                // iterate over resistors.
                // then add sum of conductances to a_ii
                for(int index = 0; index < resistors.size(); index++){
                    // If (input is i+1 and output is j+1) OR (input is j+1 and input is i+1)
                    if((resistors[index]->inputs[0] == (i+1) && resistors[index]->outputs[0] == (j+1))||(resistors[index]->inputs[0] == (j+1) && resistors[index]->outputs[0] == (i+1))){ // i+1 so that 0,0 on matrix is populated by node 1, 1,1 by node 2, etc
                        
                        // Add its conductance (1/R) to the nodeCond 
                        nodeCondNonDiag += (1/resistors[index]->ohm);
                    }
                }
                nodeCondNonDiag*=(-1);
                condMatrix[i][j] = nodeCondNonDiag;
                nodeCondNonDiag = 0;
            }

            // If voltage source:
            // add a 1 in the last column, in the row # corresponding to the node at which the voltage is impacted by the voltage source
            // add a 1 in the last row, in the column # associated with the node at which the voltage is impacted.
        }
        
    }

    // *** 
    for(int i = 0; i < condMatrixDim; i++){
        for(int j = 0; j < condMatrixDim; j++){
            std::cout << "[" << condMatrix[i][j] << "] " ;
        }
        std::cout << std::endl;
    }


    // for the number of nodes in the matrix

    // Finally, solve this matrix to get voltages at each node


}
