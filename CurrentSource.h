#include "Component.h"
#pragma once

class CurrentSource final: public Component {

    double amps;
public:
    CurrentSource();       // Constructor.
    ~CurrentSource();      // Destructor.
    void setCurrent(double amperage);  // Setting how many amps the source provides.
};