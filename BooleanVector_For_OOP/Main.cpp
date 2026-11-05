#include "BooleanVector.h"
#include <iostream>

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

    return 0;
}
