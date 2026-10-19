#include <iostream>
#include "solver_dynamic_array.h"

int main()
{
     int rawArray[] = { 10, 50, 20, 40 };
    DynamicArray<int> array1(rawArray, 4);

    std::cout << "Initial array1: " << array1 << " | Length: " << array1.getLength() << " | Capacity: " << array1.getCapacity() << std::endl;

    array1 += 99;
    std::cout << "After array1 99: " << array1 << " | Capacity: " << array1.getCapacity() << std::endl;

    return 0;
}
