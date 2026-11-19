#include <iostream>

#include "LinkedList.h"

int main()
{
        int arr[] = { 10, 20, 30, 40 };
        LinkedList<int> list1(arr, 4);
        list1.addToHead(5);
        std::cout << "addToHead: " << list1 << std::endl;
        list1.addToTail(50);
        std::cout << "addToTail 50: " << list1 << std::endl;
        list1.insertAt(2, 15);
        std::cout << "insertAt (2 15): " << list1 << std::endl;
        list1.insertAfterKey(30, 35);
        std::cout << "insertAfterKey (30 35): " << list1 << std::endl;

        std::cout << "list1: " << list1 << " (size = " << list1.getListSize() << ")" << std::endl;

        list1.removeHead();
        std::cout << "removeHead: " << list1 << std::endl;
        list1.removeTail();
        std::cout << "removeTail: " << list1 << std::endl;
        list1.removeAt(1);
        std::cout << "removeAt 1: " << list1 << std::endl;
        list1.removeByKey(35);
        std::cout << "After removeByKey 35: " << list1 << std::endl;

        LinkedList<int> list2 = list1;
        std::cout << "list1 != list2: " << (list1 != list2 ? "true" : "false") << std::endl;



    return 0;
}