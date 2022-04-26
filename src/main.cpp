#include <iostream>
#include "export.h"

EXPORT void run_platypus() {
    std::cout << "hello world!!!" << std::endl;
}

int main() {
    run_platypus();  
    return 0;
}
