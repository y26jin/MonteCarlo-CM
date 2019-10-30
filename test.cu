#include "test.cuh"
#include <iostream>
__global__ void testie(void){}

void myk() {
    testie <<<1, 1>>> ();
    std::cout << "hehe" << std::endl;
}