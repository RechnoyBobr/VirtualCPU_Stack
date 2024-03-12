#include <gtest/gtest.h>
#include "../include/stack.h"
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
        lib::Stack<float> M;
        M = K;
        EXPECT_EQ(K.top(), B.top());
        lib::Stack<float> L;
        L = std::move(B);
        lib::Stack<float> N(std::move(M));
        EXPECT_EQ(B.get_size(), -1);
    }

    TEST(test4, exception_test) {
        lib::Stack<char> f(20);
        EXPECT_THROW(f.pop(), std::runtime_error);
        for (int i = 0; i < 20; ++i) {
            f.push('a');
        }
        EXPECT_THROW(f.push('b'), std::runtime_error);
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
        F.push(std::move(f));
        EXPECT_EQ(F.top().abt, "Hi!");
        EXPECT_EQ(F.top().k, 123);
        EXPECT_EQ(F.top().f, 1.023);
    }

}