#include <iostream>
#include "solver_dynamic_array.h"
#include "IntDinamicArray.h"

int main()
{
    std::cout << "Raund 1: IntDynamicArray " << std::endl;

    int rawIntArray[] = { 10, 50, 20, 50, 30, 50, 40 };
    IntDynamicArray intArray1(rawIntArray, 7);

    std::cout << "Initial intArray1: " << intArray1 << " | Length: " << intArray1.getLength() << " | Capacity: " << intArray1.getCapacity() << std::endl;

    intArray1 += 99;
    std::cout << "After intArray1 += 99: " << intArray1 << " | Capacity: " << intArray1.getCapacity() << std::endl;

    intArray1.insertAt(2, 777);
    std::cout << "After insertAt(2, 777): " << intArray1 << std::endl;

    intArray1.removeAt(0);
    std::cout << "After removeAt(0): " << intArray1 << std::endl;

    intArray1.removeAll(50);
    std::cout << "After removeAll(50): " << intArray1 << std::endl;

    intArray1.sort();
    std::cout << "Sorted intArray1: " << intArray1 << std::endl;
    std::cout << "Min: " << intArray1.findMin() << ", Max: " << intArray1.findMax() << std::endl;

    std::cout << "\nIterating over intArray1 with range-for: ";
    for (int& value : intArray1)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    intArray1.erase(intArray1.cbegin() + 1, intArray1.cbegin() + 3);
    std::cout << "After erase range [1, 3): " << intArray1 << std::endl;

    intArray1.insert(intArray1.cbegin() + 1, 954);
    std::cout << "After insert 954 before iterator: " << intArray1 << std::endl;


    IntDynamicArray intArray2;
    intArray2 += 100;
    intArray2 += 200;
    IntDynamicArray intArray3 = intArray1 + intArray2;
    std::cout << "Summed intArray3: " << intArray3 << std::endl;


    std::cout << "\nintArray.input() output()" << std::endl;
    IntDynamicArray customIntArray;
    customIntArray.input();  
    std::cout << "result output(): ";
    customIntArray.output();
    std::cout << std::endl;

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
  
    array1.insert(array1.cbegin() + 1, 985);
    std::cout << "After insert 985 before iterator: " << array1 << std::endl;

  
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

    std::cout << "\n stringArray.input() output()" << std::endl;
    DynamicArray<std::string> customStringArray;
    customStringArray.input();
    std::cout << "result output(): ";
    customStringArray.output();
    std::cout << std::endl;

    return 0;
    }