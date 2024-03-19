#include "parser/include/parser.h"
#include "preprocessor/include/preprocessor.h"
#include <memory>
#include "emulator.h"

namespace emu {
    Emulator::Emulator(const std::string &f_path, const std::string &s_path) : preprocessor(
            preproc::Preprocessor(f_path, s_path)), deserializer(s_path) {
        operations = {
                {parser::Tokens::PUSH,  std::make_shared<Push>(stack, labels, functions, registers)},
                {parser::Tokens::POP,   std::make_shared<Pop>(stack, labels, functions, registers)},
                {parser::Tokens::PUSHR, std::make_shared<PushR>(stack, labels, functions, registers)},
                {parser::Tokens::POPR,  std::make_shared<PopR>(stack, labels, functions, registers)},
                {parser::Tokens::ADD,   std::make_shared<Sum>(stack, labels, functions, registers)},
                {parser::Tokens::SUB,   std::make_shared<Sub>(stack, labels, functions, registers)},
                {parser::Tokens::MUL,   std::make_shared<Mul>(stack, labels, functions, registers)},
                {parser::Tokens::DIV,   std::make_shared<Div>(stack, labels, functions, registers)},
                {parser::Tokens::IN,    std::make_shared<In>(stack, labels, functions, registers)},
                {parser::Tokens::OUT,   std::make_shared<Out>(stack, labels, functions, registers)}
        };
    }

    void Emulator::preprocess() {
        parser::Token token;
        std::string cur_label;
        token = deserializer.deserialize();
        while (token.type != parser::Tokens::END) {
            if (token.type == parser::Tokens::LABEL) {
                labels[token.value] = instructions.size() - 1;
                cur_label = token.value;
            } else if (token.type == parser::Tokens::RET) {
                for (unsigned long i = labels[cur_label]; i < instructions.size(); i++) {
                    functions[cur_label].emplace_back(instructions[i]);
                }
                for (int i = instructions.size(); i >= labels[cur_label]; i--) {
                    instructions.pop_back();
                }
                labels.erase(cur_label);
                functions[cur_label].emplace_back(token);
            } else {
                instructions.emplace_back(token);
            }

        }
    }

    void Emulator::run() {
        preprocessor.process_file();
        preprocessor.serialize();

    }

    void Emulator::execute() {
        int ind = 0;
        while (ind < instructions.size()) {

            operations[instructions[ind].type]->execute(instructions[ind].value);
            ind++;
        }
    }


    void Push::execute(const std::string &value) {
        long long val = std::stoll(value);
        stack->push(val);
    }

    Operation::Operation(lib::Stack<long long> &stack,
                         std::unordered_map<std::string, unsigned long> &labels,
                         std::unordered_map<std::string, std::vector<parser::Token>> &functions,
                         std::unordered_map<std::string, long long> &registers) {
        this->stack = std::make_shared<lib::Stack<long long>>(stack);
        this->labels = std::make_shared<std::unordered_map<std::string, unsigned long>>(labels);
        this->functions = std::make_shared<std::unordered_map<std::string, std::vector<parser::Token>>>(functions);
        this->registers = std::make_shared<std::unordered_map<std::string, long long>>(registers);
    }


    void Pop::execute(const std::string &value) {
        stack->pop();

    }

    void PushR::execute(const std::string &value) {
        stack->push(registers->at(value));
    }

    void PopR::execute(const std::string &value) {
        registers->at(value) = stack->pop();
    }

    void Sum::execute(const std::string &value) {
        long long res = stack->pop() + stack->pop();
        stack->push(res);
    }

    void Sub::execute(const std::string &value) {
        long long res = stack->pop() - stack->pop();
        stack->push(res);
    }

    void Mul::execute(const std::string &value) {
        long long res = stack->pop() * stack->pop();
        stack->push(res);
    }

    void Div::execute(const std::string &value) {
        long long res = stack->pop() / stack->pop();
        stack->push(res);
    }

    void In::execute(const std::string &value) {
        long long in;
        std::cin >> in;
        stack->push(in);
    }

    void Out::execute(const std::string &value) {
        std::cout << stack->pop() << std::endl;
    }


}