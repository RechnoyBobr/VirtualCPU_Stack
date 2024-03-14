#include "gtest/gtest.h"
#include "emulator.h"

namespace {
    TEST(expect_throw, out) {
        emu::Emulator emulator("tests/test1.txt");
        emulator.process_file();
    }
}