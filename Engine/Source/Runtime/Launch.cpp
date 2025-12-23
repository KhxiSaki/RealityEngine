

#include <exception>
#include <iostream>

#include "Applications.h"

int main() {
    Applications app;

    try {
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
