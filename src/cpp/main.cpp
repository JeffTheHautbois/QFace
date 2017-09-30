#include <iostream>

#include "views/stubView.h"

int main() {
    if (stubViewFunction() == 2) {
        std::cout << "It worked!" << std::endl;
    } else {
        std::cout << "It didn't work." << std::endl;
    }

    return 0;
}
