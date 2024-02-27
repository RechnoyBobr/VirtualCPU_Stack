#include <string>
#include <iostream>

namespace lib {
    template<class T>
    class Stack {
    private:
        int FIX_SIZE;
        int cur;
        T *stack;

    public:
        Stack() {
            this->FIX_SIZE = 0;
            this->cur = 0;
            this->stack = nullptr;
        }

        explicit Stack(int SIZE) {
            this->FIX_SIZE = SIZE;
            this->cur = 0;
            this->stack = new T(FIX_SIZE);
        }

        Stack(Stack &&other) noexcept {
            this->FIX_SIZE = other.FIX_SIZE;
            this->cur = other.cur;
            this->stack = other.stack;
            other.stack = nullptr;
        }

        Stack(Stack &other) {
            this->FIX_SIZE = other.FIX_SIZE;
            delete this->stack;
            this->cur = other.cur;
            this->stack = new T(FIX_SIZE);
            for (int i = 0; i < FIX_SIZE; ++i) {
                this->stack[i] = other.stack[i];
            }
        }

        Stack &operator=(Stack const &other) {
            if (this == &other) {
                return *this;
            }
            this->FIX_SIZE = other.FIX_SIZE;
            delete this->stack;
            this->cur = other.cur;
            this->stack = new T(FIX_SIZE);
            for (int i = 0; i < FIX_SIZE; ++i) {
                this->stack[i] = other.stack[i];
            }
            return *this;
        }

        Stack &operator=(Stack &&other) noexcept {
            this->FIX_SIZE = other.FIX_SIZE;
            other.FIX_SIZE = -1;
            this->stack = other.stack;
            other.stack = nullptr;
            return *this;
        }

        template<class V>
        void push(V element) {
            if (this->cur + 1 > this->FIX_SIZE) {
                throw std::runtime_error("Error: stack is full");
            }
            this->stack[cur] = element;
            this->cur++;
        }

        T pop() {
            if (cur == 0) {
                throw std::runtime_error("Error: trying to pop in empty stack");
            }
            cur--;
            return this->stack[cur];
        }

        T top() {
            return this->stack[cur];
        }

        ~Stack() {
            delete this->stack;
            this->FIX_SIZE = -1;

        }


    };


}