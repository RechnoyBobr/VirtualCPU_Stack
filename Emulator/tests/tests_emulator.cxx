#include <iostream>
#include "gtest/gtest.h"
#include "emulator.h"

namespace {
    TEST(test1, no_end) {
        emu::Emulator emulator("/home/ilya/IdeaProjects/VirtualCPU_Stack/Emulator/tests/tests1");
        EXPECT_THROW(emulator.process_file(), parser::ParserError);
    }

    TEST(test2, push_out) {
        emu::Emulator emulator("/home/ilya/IdeaProjects/VirtualCPU_Stack/Emulator/tests/tests2");
        std::cout << "Out for test 2 should be 120, it is: ";
        EXPECT_NO_FATAL_FAILURE(emulator.process_file());
    }

    TEST(test3, add_out) {
        emu::Emulator emulator("/home/ilya/IdeaProjects/VirtualCPU_Stack/Emulator/tests/tests3");
        std::cout << "Out for test 3 should be 145, it is: ";
        EXPECT_NO_FATAL_FAILURE(emulator.process_file());
    }
}