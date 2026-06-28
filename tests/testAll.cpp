#include <iostream>

#include "testAll.h"
#include "testSequence.h"
#include "testStream.h"
#include "testSort.h"

void runAllTests() {
    std::cout << "Tests for Sequence\n\n";
    runAllTestSequence();
    std::cout << "\nTests for streams\n\n";
    runAllTestStream();
    std::cout << "\nTests for stream sorting\n\n";
    runAllTestSort();
}