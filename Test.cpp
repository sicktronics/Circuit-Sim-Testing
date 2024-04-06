#include "Res_5p_Tol.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Component.h"
#include "Circuit.h"
#include <iostream>

int main(int argc, char* argv[]) {

    // Test circuit "Sample1":

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
    R2.setOhmage(5);

    Res_5p_Tol R3;
    R3.addInput(2);
    R3.addOutput(0);
    R3.setOhmage(5);

    Circuit ckt;

    Component &c_1 = C1;
    Component &r_1 = R1;
    Component &r_2 = R2;
    Component &r_3 = R3;

    // std::cout << c_1.inputs[0] << std::endl;
    // std::cout << r_1.inputs[0] << std::endl;
    // std::cout << r_2.inputs[0] << std::endl;
    // std::cout << r_3.inputs[0] << std::endl;



    Component *c01 = &c_1;
    Component *c02 = &r_1;
    Component *c03 = &r_2;
    Component *c04 = &r_3;

    ckt.addComponent(c01);
    ckt.addComponent(c02);
    ckt.addComponent(c03);
    ckt.addComponent(c04);

    // std::cout << ckt.resistors.size() << std::endl;

    // for (int i = 0; i < ckt.resistors.size(); i++)
    // {
    //     std::cout << ckt.resistors[i]->inputs[0] << std::endl;
    // }

    ckt.dcOp();

    // Res_5p_Tol r1;
    // Res_5p_Tol r2;
    // CurrentSource c1;
    // VoltageSource v1;

    // Circuit ckt;

    // Component comp1;
    // Component &comp2 = r2;
    // Component &comp3 = c1;
    // Component &comp4 = v1;

    // comp1.addInput(0);

    // // std:: cout << "hello!" << std::endl;
    // comp2.addInput(3);
    // comp3.addInput(2);
    // comp4.addInput(1);

    // // // What's with the "&"? https://stackoverflow.com/questions/8857857/how-does-the-ampersand-sign-work-in-c
    // Component *c01 = &comp1;
    // Component *c02 = &comp2;
    // Component *c03 = &comp3;
    // Component *c04 = &comp4;



    // // // Adding the component should auto sort it
    // ckt.addComponent(c01);
    // ckt.addComponent(c02);
    // ckt.addComponent(c03);
    // ckt.addComponent(c04);

    // // // expected comp order: 1, 4, 3, 2

    // for (size_t i = 0; i < ckt.components.size(); i++)
    // {
    //     std::cout << ckt.components[i]->inputs[0] << std::endl;
    //     // std::cout << ckt.components[i]->inputs[i] << std::endl;
    //     // std::cout << ckt.components[i]->inputs[i] << std::endl;

    // }
    
}