#include "Component.h"
#pragma once

struct Res_5p_Tol: Component {

    double ohm;
    Res_5p_Tol(){compID = 0;};       // Constructor that sets the compID.
    void setOhmage(double ohmage);  // setting how many ohms of resistance the resistor has.
};