#include "Res_5p_Tol.h"

// This base component class is a resistor with +/- 5 percent tolerance.


void Res_5p_Tol::setOhmage(double ohmage){

    /* TO DO: Generate error*/
    // generate +/- 5% error (generate random int(??) from -5 to +5, then divide by 100)
    // https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
    // add to ohmage

    ohm = ohmage;
}
