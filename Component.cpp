#include "Component.h"
/*
* Parent class for linear components
* Contains:
* - function for adding an input node
* - function for adding an output node
*/

void Component::addInput(int n){ // Function for adding an input node
    inputs.push_back(n); // Adding the new input node # to the list 
}   

void Component::addOutput(int n){ // Function for adding an output node
    outputs.push_back(n); // Adding the new output node # to the list
}  
