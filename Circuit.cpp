#include "Circuit.h"
#include <iostream>    

/*
* Used to add a component to the circuit.
* Uses the ID of the component to update
* tracking variables appropriately.
*/
void Circuit::addComponent(Component *compToAdd){
    // If you just added a voltage source, increase counter
    if(compToAdd->compID==1){
        numVS++;
    }
    // If you just added a current source, increase counter
    else if(compToAdd->compID==2){
        numCS++;
        // std::cout << numCS << std::endl;
    }
    // IF components size is 0, (aka first element) add to list
    if(components.size() < 1){
        components.push_back(compToAdd);
    }
    // If it's the first resistor, add it it the resistors
    if(compToAdd->compID==0 && resistors.size() < 1){
        resistors.push_back((Res_5p_Tol*)compToAdd);
    }
    // If it's the first voltage source, add it it the v sorces
    else if(compToAdd->compID==1 && vSrcs.size() < 1){
        std::cout << "t 1.5" << std::endl;
        vSrcs.push_back((VoltageSource*)compToAdd);
    }
    // If it's the first current source, add it it the c sources
    else if(compToAdd->compID==2 && cSrcs.size() < 1){
        cSrcs.push_back((CurrentSource*)compToAdd);
    }
    else{
        // Otherwise, if it's not the first element, add it 
        // to the correct list in ascending order of input node
        if(compToAdd->compID==0){   // For resistors
            for(int i = resistors.size() - 1; i >= 0 ; --i){
                if(compToAdd->inputs[0] >= resistors[i]->inputs[0]){
                    resistors.insert(resistors.begin() + (i+1), (Res_5p_Tol*)compToAdd);
                    break;
                }
            }                
        }
        else if(compToAdd->compID==1){  // For voltage sources
            for(int i = vSrcs.size() - 1; i >= 0 ; i--){
                if(compToAdd->inputs[0] >= vSrcs[i]->inputs[0]){
                    vSrcs.insert(vSrcs.begin() + (i+1), (VoltageSource*)compToAdd);
                    break;
                }
            }                
        }
        else if(compToAdd->compID==2){  // For current sources
            for(int i = cSrcs.size() - 1; i >= 0 ; i--){
                if(compToAdd->inputs[0] >= cSrcs[i]->inputs[0]){
                    cSrcs.insert(cSrcs.begin() + (i+1), (CurrentSource*)compToAdd);
                    break;
                }
            }                
        }
        // Then adding to the components list (also ascending order)
        for(int i = components.size() - 1; i >=0 ; i--){
            if(compToAdd->inputs[0] >= components[i]->inputs[0]){ 
                components.insert(components.begin() + (i+1), compToAdd);
                break;
            }
        }
    }
}

/*
* Very simple code for computing the DC operating point
* (solving the circuit) for linear components.
* Sets up a system of equations then uses LU factorization
* to solve at each node.
*/
void Circuit::dcOp(){

    for (int i = 0; i < resistors.size(); i++) { // Determining number of resistors with UNIQUE inputs
        // Move the index ahead while there are duplicates
        while (i < (resistors.size() - 1) && resistors[i]->inputs[0] == resistors[i + 1]->inputs[0]){
            i++;
        }
        numCondNodes++;
    }

    /* - - - - - 
    ~Rules of the game ~
    - Row i and col j corresponds to node i+1 or j+1
    - The FIRST node is node 1, 0 reserved for gnd!
    - TO DO : MAKE THIS MORE ROBUST 
    - - - - - */ 
    // Then build the conductance matrix: NxN (with additional row/col added for each voltage source)
    condMatrixDim = numCondNodes + numVS;

    // THE CONDUCTANCE MATRIX
    double condMatrix[condMatrixDim][condMatrixDim];

    double nodeCondDiag;               // For tracking G on a diagonal entry 
    double nodeCondNonDiag;            // For tracking G on a non-diag entry

    double solVector[condMatrixDim];   // Array to hold solutions to the ckt

    // BOOLEANS to check if a certain [i][j] should be
    // populated with a "1" to account for a voltage source
    bool fillRow = false;
    bool fillCol = false;

    // OFFSET to make sure each relevant i is reached
    int offset = 0;
    // Which row to track (to accout for voltage sources)
    int iToCheck = offset+numCondNodes;

    // For each row...
    for(int i = 0; i < condMatrixDim; i++){

        iToCheck = offset+numCondNodes;
        // Flag a row for accounting for voltage source
        if(i == iToCheck){
            fillRow = true;
        }

        // For each current source...
        for(int k = 0; k < numCS; k++){
            // ADD the values of any current sources flowing into that node (ie for which it is an output)
            if(cSrcs[k]->outputs[0]==(i+1)){
                solVector[i] += cSrcs[k]->amps;
            }
            // And SUB the values of any current sources flowing out of that node (ie for which it is an input)
            else if(cSrcs[k]->inputs[0]==(i+1)){
                solVector[i] += cSrcs[k]->amps;
            }
            // If no current sources attached, 0...
            else{
                solVector[i] = 0;
            }
        }

        // For each column...
        for (int j = 0; j < condMatrixDim; j++)
        {
            // Flag the column for filling if both the row is flagged and the col corresponds
            // to the Voltage Source output node
            if(vSrcs.size()>0){
                int currentOutputNode = vSrcs[offset]->outputs[0];
                int jToCheck = currentOutputNode - 1;
                if((fillRow == true) && (j == jToCheck)){
                    fillCol = true;
                }
            }

            // For diagonal elements, add all conductances (1/R) directly attached to i
            if(i==j){
                // Iterate over resistors.
                // Then add sum of conductances to a_ii
                for(int index = 0; index < resistors.size(); index++){
                    // If input node OR output node is (i+1)
                    if(resistors[index]->inputs[0] == (i+1) || resistors[index]->outputs[0] == (i+1)){ // i+1 so that 0,0 on matrix is populated by node 1, 1,1 by node 2, etc
                        // Add its conductance (1/R) to the nodeCond 
                        nodeCondDiag += (1/resistors[index]->ohm);
                    }
                }
                condMatrix[i][j] = nodeCondDiag; // Update matrix 
                nodeCondDiag = 0;                // Reset
            }

            // For non-diagonal elements, add all conductances directly between i and j and multiply by -1
            if(i != j){
                // Iterate over resistors.
                // Then add sum of conductances to a_ii
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

            if(fillRow && fillCol){     // Finally, if an entry is flagged for a Voltage Source, 
                condMatrix[i][j] = 1;   // Add a one to the appropriate col and row
                condMatrix[j][i] = 1;
                solVector[i] = vSrcs[offset]->volts; // Add the voltage to the proper solution vector entry
            }
            fillCol = false;    // Reset
        }
        if((offset < numVS - 1) && (fillRow)){  // Update and prepare for next row
            offset++;
        }        
        fillRow = false;
    }

    // For printing the conductance matrix
    std::cout<< "COND MATRIX: " << std::endl;
    for(int i = 0; i < condMatrixDim; i++){
        for(int j = 0; j < condMatrixDim; j++){
            std::cout << "[" << condMatrix[i][j] << "] " ;
        }
        std::cout << std::endl;
    }
    // For printing the solution vector
    // std::cout<< "SOLUTION VECTOR: " << std::endl; 
    // for(int i = 0; i < condMatrixDim; i++){
    //     std::cout << solVector[i] << std::endl;
    // }

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
    // Uncomment to print the lower and upper matrices
    // std::cout << " LOWER " << std::endl;
    // for(int i = 0; i < condMatrixDim; i++){
    //     for(int j = 0; j < condMatrixDim; j++){
    //         std::cout << "[" << l[i][j] << "] " ;
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << " UPPER " << std::endl;
    // for(int i = 0; i < condMatrixDim; i++){
    //     for(int j = 0; j < condMatrixDim; j++){
    //         std::cout << "[" << u[i][j] << "] " ;
    //     }
    //     std::cout << std::endl;
    // }

    // Now onto solving...https://www.youtube.com/watch?v=GKkUU4T6o08&t=666s
    double yVector[condMatrixDim];      
    double xVector[condMatrixDim];

    // STEP 1: Solve Ly = b using forward-sub...
    // https://courses.physics.illinois.edu/cs357/sp2020/notes/ref-9-linsys.html#:~:text=The%20forward%20substitution%20algorithm%20solves%20a%20lower%2Dtriangular%20linear%20system,xj%E2%84%93nn.
    double temp = 0.0;

    for (int i = 0; i < condMatrixDim; i++){
        // Grabbing the i-th solution vector ["b"]
        temp = solVector[i];
        // Subtracting off each of the previous row times y-values
        for(int j = 0; j < i; j++){
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
        // Subtracting off each of the previous row times y-values
        for(int j = i + 1; j < condMatrixDim; j++){
            temp -= (u[i][j] * xVector[j]);
        }   
        // Dividing by the diagonal
        xVector[i] = temp / u[i][i];
    }

    std::cout << "SOLUTION: " << std::endl;
    for(int i = 0; i < condMatrixDim; i++){
        if(i+1 > numCondNodes){
            std::cout << "Current across VS into node " << condMatrixDim - numCondNodes + numVS + 1  << ": "<< xVector[i] << "A" << std::endl;
        }
        else{
            std::cout << "Voltage at node " << i+1 << ": "<< xVector[i] << "V" << std::endl;
        }
        
    }

}
