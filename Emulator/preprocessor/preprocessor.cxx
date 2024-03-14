#include "preprocessor.h"
#include <stdexcept>


namespace preproc {

    Preprocessor::Preprocessor() {
        this->stackSize = 131072;
        this->stack = lib::Stack<long long>(this->stackSize);

    }

    Preprocessor::~Preprocessor() {
        this->stack.~Stack();
        this->stackSize = 0;
    }

    void Preprocessor::Add() {
        long long a = this->stack.pop();
        long long b = this->stack.top();
        this->stack.push(a);
        this->stack.push(a + b);
    }

    void Preprocessor::Substract() {
        long long a = this->stack.pop();
        long long b = this->stack.top();
        this->stack.push(a);
        this->stack.push(b - a);
    }

    void Preprocessor::Multiply() {
        long long a = this->stack.pop();
        long long b = this->stack.top();
        this->stack.push(a);
        this->stack.push(a * b);
    }

    void Preprocessor::Divide() {
        long long a = this->stack.pop();
        long long b = this->stack.top();
        this->stack.push(a);
        this->stack.push(b / a);
    }

    void Preprocessor::In() {
        long long a;
        std::cin >> a;
        this->stack.push(a);
    }

    void Preprocessor::Out() {
        std::cout << this->stack.pop() << std::endl;
    }

    void Preprocessor::Push(long long a) {
        this->stack.push(a);
    }

    void Preprocessor::Pop() {
        this->stack.pop();
    }

    void Preprocessor::PushR(const std::string &reg) {
        this->stack.push(this->registers[reg]);
    }

    void Preprocessor::PopR(const std::string &reg) {
        this->registers[reg] = this->stack.pop();
    }

    long long Preprocessor::get_reg(const std::string &reg) {
        return this->registers[reg];
    }

    std::optional<long long> Preprocessor::parse_number(const std::string &str) {
        try {
            return std::stoll(str);
        } catch (std::invalid_argument &e) {
            return std::nullopt;
        }
    }

    const char *PreprocessorError::what() const noexcept {
        return "Preprocessor error occurred!";
    }

}