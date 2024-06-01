#include "Component.h"
#pragma once

/*
* CurrentSource inherits from Component
* Contains:
* - field to track amps
* - setter function for amps
*/

struct CurrentSource: Component {

    double amps;
    CurrentSource(){compID=2;};       // Constructor sets component ID.
    void setCurrent(double amperage);  // Setting how many amps the source provides.
};