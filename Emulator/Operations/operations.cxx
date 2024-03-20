#include "operations.h"

namespace op {

    void Push::execute(memo::Memory &memory, const std::string &value) {
        long long val = std::stoll(value);
        memory.stack.push(val);
    }


    void Pop::execute(memo::Memory &memory, const std::string &value) {
        memory.stack.pop();

    }

    void PushR::execute(memo::Memory &memory, const std::string &value) {
        memory.stack.push(memory.registers[value]);
    }

    void PopR::execute(memo::Memory &memory, const std::string &value) {
        memory.registers[value] = memory.stack.pop();
    }

    void Sum::execute(memo::Memory &memory, const std::string &value) {
        long long res = memory.stack.pop() + memory.stack.pop();
        memory.stack.push(res);
    }

    void Sub::execute(memo::Memory &memory, const std::string &value) {
        long long first = memory.stack.pop();
        long long second = memory.stack.pop();
        long long res = second - first;
        memory.stack.push(res);
    }

    void Mul::execute(memo::Memory &memory, const std::string &value) {
        long long res = memory.stack.pop() * memory.stack.pop();
        memory.stack.push(res);
    }

    void Div::execute(memo::Memory &memory, const std::string &value) {
        long long first = memory.stack.pop();
        long long second = memory.stack.pop();
        long long res = second / first;
        memory.stack.push(res);
    }

    void In::execute(memo::Memory &memory, const std::string &value) {
        long long in;
        std::cin >> in;
        memory.stack.push(in);
    }

    void Out::execute(memo::Memory &memory, const std::string &value) {
        std::cout << memory.stack.pop() << std::endl;
    }

}