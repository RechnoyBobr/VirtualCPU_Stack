#include <iostream>
#include "emulator.h"
#include <string>
#include <cstring>


int main(int argc, const char *argv[]) {
    // When launching the program you should first pass it three arguments.
    // First is flag -p, second and third are paths to the code file and path to file for serialization.
    if (std::strcmp(argv[1], "-p") == 0) {
        try {
            emu::Emulator emulator(argv[2], argv[3]);
            emulator.run();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}