#include "Circuit.h"
#include <iostream>    

// Complexity: O(n)
void Circuit::addComponent(Component *compToAdd){
    // Check if voltage source:
    if(compToAdd->compID==1){
        numVS++;
    }
    else if(compToAdd->compID==2){
        numCS++;
    }
    // Adding the new component to the components vector
    // STEP 1 - SORT 
    // IF components size is 0, (aka first element) add to list
    if(components.size() < 1 || resistors.size() < 1 || vSrcs.size() < 1 || cSrcs.size() < 1){
        components.push_back(compToAdd);

        // Add to RES
        if(compToAdd->compID==0){
            resistors.push_back((Res_5p_Tol*)compToAdd);
        }
        else if(compToAdd->compID==1){
            vSrcs.push_back((VoltageSource*)compToAdd);
        }
        else if(compToAdd->compID==2){
            cSrcs.push_back((CurrentSource*)compToAdd);
        }
    }

    // TO DO: ADD CHECK TO MAKE SURE COMPONENT HAS BEEN INITIALIZED WITH AN INPUT AND OUTPUT NODE
    // Creating the sorted vectors
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
        else if(compToAdd->compID==1){
            for(int i = vSrcs.size() - 1; i >= 0 ; i--){
                // Add to vSrcs
                if(compToAdd->inputs[0] >= vSrcs[i]->inputs[0]){
                    vSrcs.insert(vSrcs.begin() + (i+1), (VoltageSource*)compToAdd);
                    break;
                }
            }                
        }
        else if(compToAdd->compID==2){
            for(int i = cSrcs.size() - 1; i >= 0 ; i--){
                // Add to cSrcs
                if(compToAdd->inputs[0] >= cSrcs[i]->inputs[0]){
                    cSrcs.insert(cSrcs.begin() + (i+1), (CurrentSource*)compToAdd);
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

/* - - - - - 
 ~Rules of the game ~
 row, col (i, j) corresponds to node (i+1, j+1)
 the FIRST node is node 1, 0 reserved for gnd
 TO DO : MAKE THIS MORE ROBUST
- - - - - */ 
    // Then build the conductance matrix: NxN (with additional row/col added for each voltage source)

    // TRACK DISTINCT NODES
    condMatrixDim = numCondNodes + numVS;

    // THE CONDUCTANCE MATRIX
    double condMatrix[condMatrixDim][condMatrixDim];

    double nodeCondDiag;
    double nodeCondNonDiag;

    double solVector[condMatrixDim];
    double varVector[condMatrixDim];

    // SOLUTION (CURRENT) VECTOR
    // for a node
    // ADD the values of any current sources flowing into that node (ie for which it is an output)
    // and SUB the values of any current sources flowing out of that node (ie for which it is an output)
    // if no current sources attached, issa 0...
    // IF VOLTAGE SOURCE:
        // append each one's VOLTAGE VALUE to the end of the vector

    // VARIABLE (VOLTAGE) VECTOR
        // for each node, add a variable representing the voltage at that node
        // IF VOLTAGE SOURCE:
        //  append each one's current to the end of the vector


    // TO DO: ELSE, THAT VALUE IS 0 (sparse matrix)

    // For each row...
    for(int i = 0; i < condMatrixDim; i++){

            // TO DO: Fix seg fault

            // SOLUTION (CURRENT) VECTOR --> note condMatrixDim=Dim of solution vector
            // for a node
            for(int k = 0; k < numCS; k++){
                // ADD the values of any current sources flowing into that node (ie for which it is an output)
                if(cSrcs[k]->outputs[0]==(i+1)){
                    solVector[i] += cSrcs[k]->amps;
                }
                // and SUB the values of any current sources flowing out of that node (ie for which it is an input)
                else if(cSrcs[k]->inputs[0]==(i+1)){
                    solVector[i] += cSrcs[k]->amps;
                }
                // if no current sources attached, issa 0...
                else{
                    solVector[i] = 0;
                }
            }
            // IF VOLTAGE SOURCE:
                // append each one's VOLTAGE VALUE to the end of the vector


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
            if(i != j){
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

            // If we are assessing the rows dedicated to voltage sources
            if(i >= numCondNodes){
                for(int index = 0; index < vSrcs.size(); index++){

                    // then if vsrc at node 1 gets hit on the col sweep
                    if(vSrcs[index]->outputs[0] == (j+1)){
                        // insert its value
                        condMatrix[i][j] = 1;
                        solVector[i] = vSrcs[index]->volts; 
                    }
                    // add a 1 in the last column, in the row # corresponding to the node at which the voltage is impacted by the voltage source
                    if(j >= numCondNodes){
                        condMatrix[(vSrcs[index]->outputs[0]) - 1][j] = 1;
                    }
                    // std::cout << j << std::endl;
                    // and then remove it (this way you don't duplicate vsrcs)
                    // NOTE: as of 5/2, this does not appear to be an issue
                    // vSrcs.erase(vSrcs.begin() + (index));
                }
            }
        }        
    }

    // for printing the conductance matrix
    for(int i = 0; i < condMatrixDim; i++){
        for(int j = 0; j < condMatrixDim; j++){
            std::cout << "[" << condMatrix[i][j] << "] " ;
        }
        std::cout << std::endl;
    }
    std::cout<< "SOL VECTOR" << std::endl;
    for(int i = 0; i < condMatrixDim; i++){

        std::cout << solVector[i] << std::endl;
    }





    // for the number of nodes in the matrix

    // Finally, solve this matrix to get voltages at each node


}
