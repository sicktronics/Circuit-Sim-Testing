#include "Component.h"
#pragma once

/*
* Res_5p_Tol inherits from Component
* Contains:
* - field to track ohmage
* - setter function for ohmage
* Note: accouting for 5p error not built yet
*/

struct Res_5p_Tol: Component {

    double ohm;
    Res_5p_Tol(){compID = 0;};       // Constructor that sets the compID.
    void setOhmage(double ohmage);  // setting how many ohms of resistance the resistor has.
};