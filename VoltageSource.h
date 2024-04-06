#include "Component.h"
#pragma once

struct VoltageSource: Component {
    double volts;
    VoltageSource(){compID=1;};       // Constructor sets component ID.
    void setVoltage(double voltage);  // Setting how many volts the source provides.
};