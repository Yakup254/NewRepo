#include <iostream>
#include "BooleanMatrix.h"

int main()
{

    BooleanMatrix m1(3, 4, false);

    std::cout << "Matrix m1 (" << m1.getRowsCount() << "x" << m1.getColumnsCount() << ")" << std::endl;
    std::cout << m1 << std::endl;

    BooleanMatrix m2(3, 4, true);
    m1.swap(m2);
    std::cout << "Matrix m1 after swap:" << std::endl << m1 << std::endl;


    return 0;
}
