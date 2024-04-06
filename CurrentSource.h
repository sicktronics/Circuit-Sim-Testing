#include "Component.h"
#pragma once

struct CurrentSource: Component {

    double amps;
    CurrentSource(){compID=2;};       // Constructor sets component ID.
    void setCurrent(double amperage);  // Setting how many amps the source provides.
};