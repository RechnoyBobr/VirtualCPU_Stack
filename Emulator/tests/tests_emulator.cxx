#include "gtest/gtest.h"
#include "emulator.h"
namespace {
    TEST(basic_push, out) {
        emu::Emulator emulator("tests/test1.txt");
        emulator.process_file();
        ASSERT_;
    }
}