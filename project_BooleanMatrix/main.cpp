#include <iostream>
#include "BooleanMatrix.h"

int main()
{

    BooleanMatrix m1(4, 5, false);

    for (uint32_t i = 0; i < m1.getRowsCount(); ++i)
    {
        for (uint32_t j = 0; j < m1.getColumnsCount(); ++j)
        {
            m1[i][j] = ((i + j) % 2 == 0);
        }
    }
    std::cout << "Matrix m1 (" << m1.getRowsCount() << "x" << m1.getColumnsCount() << ")" << std::endl;
    std::cout << m1 << std::endl;
    std::cout << "Weight m1: " << m1.getWeight() << std::endl;

    BooleanMatrix testMatrix1(10, 10, false);
    std::cout << testMatrix1 << std::endl;
    std::cout << "Initial testMatrix1 weight: " << testMatrix1.getWeight() << std::endl;

    uint32_t matrixSize = testMatrix1.getRowsCount();

    for (uint32_t i = 0; i < matrixSize; i=i+2)
    {
        testMatrix1[i][i] = true;
    }

    std::cout << "Diagonal testMatrix1:" << std::endl << testMatrix1;
    std::cout << "testMatrix1 weight: " << testMatrix1.getWeight() << std::endl;
    std::cout << "Total weight: " << testMatrix1.getWeight() << ", Row 1 weight: " << testMatrix1.getRowWeight(0) << std::endl;
    std::cout << std::endl;

    testMatrix1.setComponents(2, 0, 3, true);
    testMatrix1.invertComponent(1, 0);
    testMatrix1.invertComponents(9, 2, 3);
    std::cout << "After modifications:\n" << testMatrix1 << std::endl;

    BooleanMatrix testMatrix2(3, 5, false);
    std::cout << testMatrix2 << std::endl;

    for (uint32_t i = 0; i < testMatrix2.getRowsCount(); ++i)
    {
        for (uint32_t j = 0; j < testMatrix2.getColumnsCount(); ++j)
        {
            testMatrix2[i][j] = 1;
        }
    }
    std::cout << "Satir sayisi: " << testMatrix2.getRowsCount() << std::endl;
    std::cout << "Sutun sayisi: " << testMatrix2.getColumnsCount() << std::endl;
    std::cout << testMatrix2 << std::endl;
    const char* rawA[] = {
       "10101",
       "11100",
       "10011"
    };
    const char* rawB[] = {
        "11001",
        "01010",
        "10101"
    };

    BooleanMatrix A(rawA, 3, 5);
    BooleanMatrix B(rawB, 3, 5);

    std::cout << "Matrix A:" << std::endl << A;
    std::cout << "Matrix B:" << std::endl << B;

    std::cout << "All rows conjunction (A): " << A.getAllRowsConjunction() << std::endl;
    std::cout << "All rows disjunction (A): " << A.getAllRowsDisjunction() << std::endl;

    std::cout << "A & B:" << std::endl << (A & B);
    std::cout << "A | B:" << std::endl << (A | B);
    std::cout << "A ^ B:" << std::endl << (A ^ B);
    std::cout << "~A:" << std::endl << (~A) << std::endl;

    std::cout << "Enter matrix (rows cols, then 0/1 bits): ";
    BooleanMatrix userMatrix;
    if (std::cin >> userMatrix)
    {
        std::cout << "Your matrix (weight = " << userMatrix.getWeight() << "):" << std::endl << userMatrix;
    }

    BooleanMatrix testMatrix4;

    testMatrix4.input();
    testMatrix4.output();


    return 0;
}
