#include <iostream>
#include "Line.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    Line line1(2  , -3  , 5  );
    line1.printLine();
    return 0;
}
