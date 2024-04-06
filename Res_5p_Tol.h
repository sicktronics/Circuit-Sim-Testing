#include "Component.h"
#pragma once

struct Res_5p_Tol: Component {

    double ohm;
    // int compID = 0;
    Res_5p_Tol(){compID = 0;};       // Constructor.
    // ~Res_5p_Tol();      // Destructor.
    void setOhmage(double ohmage);  // setting how many ohms of resistance the resistor has.

};