#include "Res_5p_Tol.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Component.h"
#include "Circuit.h"
#include <iostream>

int main(int argc, char* argv[]) {

    /*
    * TEST 1: SIMPLE CIRCUIT W/ 2 NODES, 1 CURRENT SOURCE, and 3 R
    * TAKEN FROM: https://youtu.be/Zk0y4J8y9nY?si=kMS9s9JxLPHPoqDq&t=772
    */
    // CurrentSource C1;
    // C1.addInput(0);
    // C1.addOutput(1);
    // C1.setCurrent(1.0);

    // Res_5p_Tol R1;
    // R1.addInput(1);
    // R1.addOutput(2);
    // R1.setOhmage(10);

    // Res_5p_Tol R2;
    // R2.addInput(2);
    // R2.addOutput(0);
    // R2.setOhmage(10);

    // Res_5p_Tol R3;
    // R3.addInput(2);
    // R3.addOutput(0);
    // R3.setOhmage(10);

    // Circuit ckt;

    // Component &c_1 = C1;
    // Component &r_1 = R1;
    // Component &r_2 = R2;
    // Component &r_3 = R3;

    // Component *c01 = &c_1;
    // Component *c02 = &r_1;
    // Component *c03 = &r_2;
    // Component *c04 = &r_3;

    // ckt.addComponent(c01);
    // ckt.addComponent(c02);
    // ckt.addComponent(c03);
    // ckt.addComponent(c04);

    // ckt.dcOp();

    /*
    * TEST 2: SIMPLE CIRCUIT W/ 4 NODES, 1 CURRENT SOURCE, 1 VOLT SOURCE and 6 R
    * TAKEN FROM: https://youtu.be/Zk0y4J8y9nY?si=M1IrttoErY3tdeoU&t=985
    */
    CurrentSource C1;
    C1.addInput(0);
    C1.addOutput(1);
    C1.setCurrent(1.0);

    Res_5p_Tol R1;
    R1.addInput(1);
    R1.addOutput(2);
    R1.setOhmage(10);

    Res_5p_Tol R2;
    R2.addInput(2);
    R2.addOutput(0);
    R2.setOhmage(10);

    Res_5p_Tol R3;
    R3.addInput(2);
    R3.addOutput(3);
    R3.setOhmage(10);

    VoltageSource V1;
    V1.addInput(0);
    V1.addOutput(3);
    V1.setVoltage(1.0);

    Res_5p_Tol R4;
    R4.addInput(3);
    R4.addOutput(0);
    R4.setOhmage(10);

    Res_5p_Tol R5;
    R5.addInput(3);
    R5.addOutput(4);
    R5.setOhmage(10);

    Res_5p_Tol R6;
    R6.addInput(4);
    R6.addOutput(0);
    R6.setOhmage(10);

    Circuit ckt;

    Component &c_1 = C1;
    Component &v_1 = V1;
    Component &r_1 = R1;
    Component &r_2 = R2;
    Component &r_3 = R3;
    Component &r_4 = R4;
    Component &r_5 = R5;
    Component &r_6 = R6;

    Component *c01 = &c_1;
    Component *c02 = &v_1;
    Component *c03 = &r_1;
    Component *c04 = &r_2;
    Component *c05 = &r_3;
    Component *c06 = &r_4;
    Component *c07 = &r_5;
    Component *c08 = &r_6;

    ckt.addComponent(c01);
    ckt.addComponent(c02);
    ckt.addComponent(c03);
    ckt.addComponent(c04);
    ckt.addComponent(c05);
    ckt.addComponent(c06);
    ckt.addComponent(c07);
    ckt.addComponent(c08);

    // std::cout << ckt.resistors.size() << std::endl;


    ckt.dcOp();


}