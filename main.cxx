#include <iostream>
#include "emulator.h"
#include <string>
#include <cstring>


int main(int argc, const char *argv[]) {
    if (std::strcmp(argv[1], "-p") == 0) {
        try {
            emu::Emulator emulator(argv[2]);
            emulator.process_file();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}