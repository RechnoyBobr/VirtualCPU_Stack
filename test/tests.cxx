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

//    TEST(test2, float_stack) {
//        lib::Stack<double> S(5);
//        double l = 1.01;
//        for (int i = 0; i < 5; ++i) {
//            l *= l;
//            S.push(l);
//        }
//        double res = S.pop();
//        EXPECT_EQ(res, l);
//        std::cout << 'A';
//    }
}