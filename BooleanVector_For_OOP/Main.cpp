#include "BooleanVector.h"
#include <iostream>
#include <sstream>

int main()
{
    std::cout << "String Constructor and Stream Output" << std::endl;
    BooleanVector vectorA("1100");
    BooleanVector vectorB("1010");

    std::cout << "Vector A: " << vectorA << " | Total Bits: " << vectorA.getBitsCount() << "\n";
    std::cout << "Vector B: " << vectorB << " | Vector Weight: " << vectorB.weight() << "\n";

    std::cout << "Logic Operations (&, |, ^, ~)" << std::endl;

    std::cout << "A & B (AND) : " << (vectorA & vectorB) << std::endl;;
    std::cout << "A | B (OR)  : " << (vectorA | vectorB) << std::endl;
    std::cout << "A ^ B (XOR) : " << (vectorA ^ vectorB) << std::endl;
    std::cout << "~A    (NOT) : " << (~vectorA) << std::endl;

    BooleanVector copyOfA(vectorA);
    std::cout << "Original Vector A: " << vectorA << std::endl;
    std::cout << "Copy of Vector A : " << copyOfA << std::endl;

    std::cout << "\nModifying the copy (setting bit at index 3 to true)..." << std::endl;
    copyOfA.setValue(3, true);

    std::cout << "Modified Copy    : " << copyOfA << std::endl;
    std::cout << "Original Vector A: " << vectorA << std::endl;

    BooleanVector invertTest("1010");
    std::cout << "Initial vector              : " << invertTest << std::endl;
    std::cout << "Checking bit status at idx 1: " << invertTest[1] << std::endl;

    invertTest.invertBit(1);
    std::cout << "Vector after invertBit  : " << invertTest << std::endl;
    std::cout << "New bit status at idx 1   : " << invertTest[1] << std::endl;
    std::cout << std::endl;

    BooleanVector shiftVector("00001111");
    std::cout << "Original vector : " << shiftVector << std::endl;
    std::cout << "Shift left  (>>2): " << (shiftVector >> 2) << std::endl;
    std::cout << "Shift right (<<2): " << (shiftVector << 2) << std::endl;
    
    BooleanVector rangeVector(12, false);
    std::cout << "Initial zeros   : " << rangeVector << std::endl;

    rangeVector.setRange(4, 5, true);
    std::cout << "After setRange  : " << rangeVector << std::endl;

    BooleanVector bitRefVector("00000000");
    std::cout << "Initial vector  : " << bitRefVector << std::endl;

    bitRefVector[2] |= true;
    bitRefVector[5] ^= true;
    std::cout << "After |= and ^= : " << bitRefVector << std::endl;
    std::cout << "Total bits count: " << bitRefVector.getBitsCount() << std::endl;
    std::cout << "Vector weight   : " << bitRefVector.weight() << std::endl;

    std::stringstream StreamInputNumber;
    BooleanVector strVector;
    StreamInputNumber << "11100011";
    StreamInputNumber >> strVector;

    std::cout << "Vector read from stream: " << strVector << std::endl;
    
    return 0;
}
