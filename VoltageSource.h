#include "Component.h"
#pragma once

struct VoltageSource: Component {

    // int compID = 1;
    double volts;
    VoltageSource(){compID=1;};       // Constructor.
    // ~VoltageSource();      // Destructor.
    void setVoltage(double voltage);  // Setting how many volts the source provides.
};