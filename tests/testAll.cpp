#include <iostream>

#include "testAll.h"
#include "testSequence.h"
#include "testSort.h"

void runAllTests() {
    std::cout << "Tests for Sequence\n\n";
    runAllTestSequence();
    std::cout << "\nTests for stream sorting\n\n";
    runAllTestSort();
}