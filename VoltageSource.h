#include "Component.h"

class VoltageSource final: public Component {

    double volts;
public:
    VoltageSource();       // Constructor.
    ~VoltageSource();      // Destructor.
    void setVoltage(double voltage);  // Setting how many volts the source provides.
};