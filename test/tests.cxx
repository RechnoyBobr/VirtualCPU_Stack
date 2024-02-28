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
        EXPECT_EQ(H.pop(), 1.2491203);
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

    TEST(test4, exception_test) {
        lib::Stack<char> f(20);
        try {
            f.pop();
        } catch (const std::runtime_error &err) {
            EXPECT_EQ(*err.what(), *std::runtime_error("Error: stack is full").what());
        }
    }

    TEST(test5, string_test) {
        lib::Stack<std::string> S(1);
        S.push("Hello, world!");
        EXPECT_EQ(S.pop(), "Hello, world!");
    }

    TEST(test6, vector_test) {
        lib::Stack<std::vector<int>> F(2);
        F.push({1, 4, 2, 13});
        EXPECT_EQ(F.pop()[3], 13);
    }

    TEST(test7, custom_type_test) {
        typedef struct test {
            int k;
            double f;
            std::string abt;
        } test;
        lib::Stack<test> F(10);
        test f;
        f.abt = "Hi!";
        f.k = 123;
        f.f = 1.023;
        F.push(f);
        EXPECT_EQ(F.top().abt, "Hi!");
        EXPECT_EQ(F.top().k, 123);
        EXPECT_EQ(F.top().f, 1.023);
    }

}