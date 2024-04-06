#include "Component.h"
#pragma once

struct CurrentSource: Component {

    double amps;
    // int compID = 2;

    CurrentSource(){compID=2;};       // Constructor.
    // ~CurrentSource();      // Destructor.
    void setCurrent(double amperage);  // Setting how many amps the source provides.
};