#include "Res_5p_Tol.h"
#include "VoltageSource.h"
#include "CurrentSource.h"
#include "Component.h"
#include "Circuit.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // 3/31 initial test works
    // std::cout << "hello" << std::endl;

    // Upon declaration, components size is 0
    // Circuit ckt;
    Res_5p_Tol r1;
    VoltageSource v1;
    CurrentSource c1;
    std::cout << r1.compID << std::endl;
    std::cout << v1.compID << std::endl;
    std::cout << c1.compID << std::endl;


    Component &comp1 = r1;
    // std::cout << c1.returnCompID() << std::endl;
    // Component *c3;

    // Component *c1p = &c1;

    // c1->addInput(5);
    // c2->addInput(7);
    // c3->addInput(6);
    // std::cout << ckt.components.size() << std::endl;
    // ckt.addComponent(c1);
    // ckt.addComponent(c2);
    // ckt.addComponent(c3);
    // for(int i = 0; i < ckt.components.size(); i++){
    //     std::cout << ckt.components[i] << std::endl;
    // }


    // int len = ckt->Circuit::getCompLen();
    
    



}