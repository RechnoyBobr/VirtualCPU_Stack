#include <gtest/gtest.h>
#include "../include/stack.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace {

    TEST(test1, int_stack) {
        lib::Stack<int> F(100);
        F.push(13);
        F.top();
        EXPECT_EQ(F.pop(), 13);
    }

    TEST(test2, double_stack) {
        lib::Stack<double> H(10);
        H.push(1.2491203);
        std::cout << H.top() << "\n";
    }

    TEST(test3, copy_stack) {
        lib::Stack<float> B(13);
        float k = 10;
        for (int i = 0; i < 13; ++i) {
            k += 0.383;
            B.push(k);
        }
        lib::Stack<float> K(B);
        EXPECT_EQ(K.top(), B.top());
        lib::Stack<float> L = std::move(B);
        EXPECT_EQ(B.get_size(), -1);
    }
}