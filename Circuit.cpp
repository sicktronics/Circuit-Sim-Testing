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
        std::cout << numCS << std::endl;
    }
    // Adding the new component to the components vector
    // STEP 1 - SORT 
    // IF components size is 0, (aka first element) add to list
    if(components.size() < 1){
        std::cout << "t 1" << std::endl;
        components.push_back(compToAdd);
    }
    // Add to RES
    if(compToAdd->compID==0 && resistors.size() < 1){
        resistors.push_back((Res_5p_Tol*)compToAdd);
    }
    else if(compToAdd->compID==1 && vSrcs.size() < 1){
        std::cout << "t 1.5" << std::endl;
        vSrcs.push_back((VoltageSource*)compToAdd);
    }
    else if(compToAdd->compID==2 && vSrcs.size() < 1){
        cSrcs.push_back((CurrentSource*)compToAdd);
    }
    else{
        std::cout << "t 2" << std::endl;
        // FOR COND MATRIX
        if(compToAdd->compID==0){
            // std::cout << "successful" << std::endl;
            for(int i = resistors.size() - 1; i >= 0 ; --i){
                std::cout << "successful 1" << std::endl;
                std::cout << compToAdd->inputs[0] << std::endl;
                // Add to RES
                if(compToAdd->inputs[0] >= resistors[i]->inputs[0]){
                    resistors.insert(resistors.begin() + (i+1), (Res_5p_Tol*)compToAdd);
                    std::cout << "successful 2" << std::endl;
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

    std::cout << "dc op 1" << std::endl;

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
    // std::cout << "number of : " << numVS << std::endl;

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

    // BOOLEANS to check if a certain [i][j] should be
                // populated with a "1" to account for a vs
    bool fillRow = false;
    bool fillCol = false;

    // OFFSET to make sure each relevant i is reached
    int offset = 0;
    int iToCheck = offset+numCondNodes;

    // For each row...
    for(int i = 0; i < condMatrixDim; i++){

        iToCheck = offset+numCondNodes;
        std::cout << "i to check: " << iToCheck << std::endl;

        if(i == iToCheck){
            fillRow = true;
            std::cout << "fill row!" << std::endl;
        }
            // SOLUTION (CURRENT) VECTOR --> note condMatrixDim=Dim of solution vector
            // for a node
            std::cout << "c 1" << std::endl;
            std::cout << numCS << std::endl;

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


            // flag the column for filling if both the row is flagged and the col corresponds to the output node
            if(vSrcs.size()>0){
                int currentOutputNode = vSrcs[offset]->outputs[0];
                int jToCheck = currentOutputNode - 1;
                if((fillRow == true) && (j == jToCheck)){
                    fillCol = true;
                    std::cout << "fill col!" << std::endl;
                }

            }




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

            if(fillRow && fillCol){
                condMatrix[i][j] = 1;
                condMatrix[j][i] = 1;
                solVector[i] = vSrcs[offset]->volts;
            }
            fillCol = false;
        }
        if((offset < numVS - 1) && (fillRow)){
            offset++;
        }        
        fillRow = false;
        
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
    // Finally, solve this matrix to get voltages at each node

    double l[condMatrixDim][condMatrixDim];
    double u[condMatrixDim][condMatrixDim];

    // Using LU factorization: https://www.tutorialspoint.com/cplusplus-program-to-perform-lu-decomposition-of-any-matrix
    for (int i = 0; i < condMatrixDim; i++) {
        for (int j = 0; j < condMatrixDim; j++) {
            if (j < i){
                l[j][i] = 0;
            } else {
                l[j][i] = condMatrix[j][i];
                for (int k = 0; k < i; k++) {
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for (int j = 0; j < condMatrixDim; j++) {
            if (j < i){
                u[i][j] = 0;
            } else if (j == i){
                u[i][j] = 1;
            } else {
                u[i][j] = condMatrix[i][j] / l[i][i];
                for (int k = 0; k < i; k++) {
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }  
            }
        }
    }

    std::cout << " LOWER " << std::endl;
    for(int i = 0; i < condMatrixDim; i++){
        for(int j = 0; j < condMatrixDim; j++){
            std::cout << "[" << l[i][j] << "] " ;
        }
        std::cout << std::endl;
    }
    std::cout << " UPPER " << std::endl;
    for(int i = 0; i < condMatrixDim; i++){
        for(int j = 0; j < condMatrixDim; j++){
            std::cout << "[" << u[i][j] << "] " ;
        }
        std::cout << std::endl;
    }

    // Now onto solving...https://www.youtube.com/watch?v=GKkUU4T6o08&t=666s
    double yVector[condMatrixDim];      
    double xVector[condMatrixDim];

    // STEP 1: Solve Ly = b using forward-sub...https://courses.physics.illinois.edu/cs357/sp2020/notes/ref-9-linsys.html#:~:text=The%20forward%20substitution%20algorithm%20solves%20a%20lower%2Dtriangular%20linear%20system,xj%E2%84%93nn.

    double temp = 0.0;

    for (int i = 0; i < condMatrixDim; i++){

        // Grabbing the i-th solution vector ["b"]
        temp = solVector[i];

        // subtracting off each of the previous row times y-values
        for(int j = 0; j < i/*-1?*/; j++){
            temp -= (l[i][j] * yVector[j]);
        }

        // Dividing by the diagonal
        yVector[i] = temp / l[i][i];
    }

    // STEP 2: Solve Ux = y to find x using backwards sub
    // double currentResult = 0.0;
    // double cumulativeSum = 0.0;

    for(int i = condMatrixDim - 1; i >= 0; i--){

        // Grabbing the i-th y vector ["b"]
        temp = yVector[i];

        // subtracting off each of the previous row times y-values
        for(int j = i + 1; j < condMatrixDim; j++){
            temp -= (u[i][j] * xVector[j]);
        }   
        // Dividing by the diagonal
        xVector[i] = temp / u[i][i];
    }

    for(int k = 0; k < condMatrixDim; k++){
        std::cout << "X vector at node " << k+1 << ": " << xVector[k] << std::endl;
    }


}
