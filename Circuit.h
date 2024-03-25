#include <vector>
#include "Component.h"

// Circuit class is where chained components are added and analysis is performed
// Start w DC OP analysis, don't worry about AC tran for now

class Circuit {
    std::vector<Component*> components;    // Vector of circuit components
public:
    Circuit();                    // Constructor.
    virtual ~Circuit();           // Destructor.

    void addComponent(Component *compToAdd); // Adding a component to the netlist
    // TO ADD:
    //  function for analysis of a circuit..
    //  void dcAnalysis() or summat
};