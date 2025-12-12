#include <hackertoolkit/htk-defer.h>
#include <iostream>

static void freeMemory(const int* memory) {
    delete memory;
    std::cout << "Memory freed!\n";
}

int main() {
    {
        HTK_DEFER{
            std::cout << "World!\n";
        };
        HTK_DEFER{
            std::cout << "Hello ";
        };
    }
    {
        const int* someMemory{ new int{ 5 } };
        HTK_DEFER{
            freeMemory(someMemory);
        };
        std::cout << "Doing some work...\n";
    }
    return 0;
}
