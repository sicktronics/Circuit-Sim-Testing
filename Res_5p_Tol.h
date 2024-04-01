#include "Component.h"
#pragma once

class Res_5p_Tol final: public Component {

    double ohm;
public:
    Res_5p_Tol();       // Constructor.
    ~Res_5p_Tol();      // Destructor.
    void setOhmage(double ohmage);  // setting how many ohms of resistance the resistor has.

};