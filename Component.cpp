#include "Component.h"

void Component::addInput(int n){ // Function for adding an input node
    inputs.push_back(n); // Adding the new node # to the list 
}   

void Component::addOutput(int n){ // Function for adding an output node
    outputs.push_back(n); // Adding the new node # to the list
}  

// Return the component ID (0 = r, 1 = vs, 2 = cs)
int Component::returnCompID(){
    return compID;
}