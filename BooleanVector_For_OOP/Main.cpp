#include "BooleanVector.h"
#include <iostream>

int main()
{

    BooleanVector testVector1(16, false);
    BooleanVector testVector2(20, true);
    BooleanVector testVector3(24, false);
    BooleanVector testVector4(32, true);

    std::cout << "source vectors\n";
    std::cout << "v1 (16, false): " << testVector1 << std::endl;
    std::cout << "v2 (20, true) : " << testVector2 << std::endl;
    std::cout << "v3 (24, false): " << testVector3 << std::endl;
    std::cout << "v4 (32, true) : " << testVector4 << std::endl;
    std::cout << "\n";

    for (uint32_t i = 0; i < testVector1.getBitsCount(); i += 4)
    {
        testVector1[i] = true;
    }

    for (uint32_t i = 0; i < testVector2.getBitsCount(); i += 4)
    {
        testVector2[i] = false;
    }

    for (uint32_t i = 0; i < testVector3.getBitsCount(); i += 8)
    {
        testVector3[i] = true;
    }

    for (uint32_t i = 0; i < testVector4.getBitsCount(); i += 8)
    {
        testVector4[i] = false;
    }

    std::cout << "v1 : " << testVector1 << std::endl;
    std::cout << "v2 : " << testVector2 << std::endl;
    std::cout << "v3 : " << testVector3 << std::endl;
    std::cout << "v4 : " << testVector4 << std::endl;

    return 0;
}
