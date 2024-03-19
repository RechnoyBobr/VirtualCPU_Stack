#pragma once

#include <string>
#include <iostream>

namespace lib {
    template<class T>
    class Stack {
    private:
        unsigned int FIX_SIZE;
        int cur;
        T *stack = nullptr;

    public:
        Stack() : FIX_SIZE(0), cur(0), stack(nullptr) {};

        explicit Stack(unsigned int SIZE) : FIX_SIZE(SIZE), cur(0) {
            this->stack = new T[FIX_SIZE];
        }

        Stack(Stack &&other) noexcept: FIX_SIZE(other.FIX_SIZE), cur(other.cur), stack(other.stack) {
            other.stack = nullptr;
            other.FIX_SIZE = -1;
        }

        Stack(Stack &other) : FIX_SIZE(other.FIX_SIZE), cur(other.cur) {
            this->stack = new T[other.FIX_SIZE];
            for (int i = 0; i < cur; i++) {
                stack[i] = other.stack[i];
            }
        }

        Stack &operator=(Stack const &other) {
            if (this == &other) {
                return *this;
            }
            this->FIX_SIZE = other.FIX_SIZE;
            if (this->stack != nullptr) {
                delete this->stack;
            }
            this->cur = other.cur;
            this->stack = new T[FIX_SIZE];
            for (int i = 0; i < FIX_SIZE; ++i) {
                this->stack[i] = other.stack[i];
            }
            return *this;
        }

        Stack &operator=(Stack &&other) noexcept {
            this->FIX_SIZE = other.FIX_SIZE;
            this->cur = other.cur;
            other.FIX_SIZE = -1;
            this->stack = other.stack;
            other.stack = nullptr;
            return *this;
        }

        [[nodiscard]] int get_size() const {
            return this->FIX_SIZE;
        }

        void push(T element) {
            if (this->cur + 1 > this->FIX_SIZE) {
                throw std::runtime_error("Error: stack is full");
            }
            this->stack[cur] = element;
            this->cur++;
        }

        void push(T &&element) {
            if (this->cur + 1 > this->FIX_SIZE) {
                throw std::runtime_error("Error: stack is full");
            }
            this->stack[cur] = std::move(element);
            this->cur++;
        }

        T pop() {
            if (cur == 0) {
                throw std::runtime_error("Error: trying to pop in empty stack");
            }
            cur--;
            return this->stack[cur];
        }

        T &top() {
            return this->stack[cur - 1];
        }

        ~Stack() {
            if (FIX_SIZE != -1) { // Means that stack was already freed
                delete[] this->stack;
                this->stack = nullptr;
                FIX_SIZE = -1;
            }
        }


    };


}