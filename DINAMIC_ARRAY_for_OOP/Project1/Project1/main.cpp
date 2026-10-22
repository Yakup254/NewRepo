#include <iostream>
#include "solver_dynamic_array.h"

int main()
{
    int rawArray[] = { 10, 50, 20, 50, 30,50, 40 };
    DynamicArray<int> array1(rawArray, 7);

    std::cout << "Initial array1: " << array1 << " | Length: " << array1.getLength() << " | Capacity: " << array1.getCapacity() << std::endl;

    array1 += 99;
    std::cout << "After array1 += 99: " << array1 << " | Capacity: " << array1.getCapacity() << std::endl;
    
    array1.insertAt(2, 777);
    std::cout << "After insertAt(2, 777): " << array1 << std::endl;

    array1.removeAt(0);
    std::cout << "After removeAt(0): " << array1 << std::endl;

    array1.removeAll(50);
    std::cout << "After removeAll(50): " << array1 << std::endl;

    array1.sort();
    std::cout << "Sorted array1: " << array1 << std::endl;
    std::cout << "Min: " << array1.findMin() << ", Max: " << array1.findMax() << std::endl;

  
    std::cout << "\nIterating over array1 with range-for: ";
    for (int& value : array1)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    array1.erase(array1.cbegin() + 1, array1.cbegin() + 3);
    std::cout << "After erase range [1, 3): " << array1 << std::endl;
  
  
    DynamicArray<int> array2;
    array2 += 100;
    array2 += 200;
    DynamicArray<int> array3 = array1 + array2;
    std::cout << "Summed array3: " << array3 << std::endl;


    std::cout << "\n Template_Test_String " << std::endl;
    DynamicArray<std::string> stringArray;
    stringArray += "C++";
    stringArray += "Template";
    stringArray += "DynamicArray";

    std::cout << "stringArray: " << stringArray << std::endl;
    stringArray.sort();
    std::cout << "Sorted stringArray: " << stringArray << std::endl;

    return 0;
    }