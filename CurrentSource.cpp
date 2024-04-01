#include "CurrentSource.h"

// This base component class is a current source.

// Function for adding amperage to source.
void CurrentSource::setCurrent(double amperage){
    amps = amperage;
}

CurrentSource::CurrentSource(){
    compID = 2;
}