#include <iostream>
#include "solver_dynamic_array.h"

int main()
{
    int rawArray[] = { 10, 50, 20, 50, 30, 40 };
    DynamicArray<int> array1(rawArray, 6);

    array1.insertAt(2, 777);
    std::cout << "After insertAt(2, 777): " << array1 << std::endl;

    array1.removeAt(0);
    std::cout << "After removeAt(0): " << array1 << std::endl;

    array1.removeAll(50);
    std::cout << "After removeAll(50): " << array1 << std::endl;

    array1.sort();
    std::cout << "Sorted array1: " << array1 << " | Min: " << array1.findMin() << ", Max: " << array1.findMax() << std::endl;

    DynamicArray<int> array2;
    array2 += 100;
    DynamicArray<int> array3 = array1 + array2;
    std::cout << "Summed array3: " << array3 << std::endl;

    return 0;
    }