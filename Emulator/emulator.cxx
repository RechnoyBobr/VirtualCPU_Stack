#include "parser/include/parser.h"
#include "preprocessor/include/preprocessor.h"
#include <memory>
#include "emulator.h"

namespace emu {
    Emulator::Emulator(const std::string &f_path, const std::string &s_path) : preprocessor(
            preproc::Preprocessor(f_path, s_path)), deserializer(s_path) {
        operations = {
                {parser::Tokens::PUSH,  std::make_shared<Push>(stack, labels, functions)},
                {parser::Tokens::POP,   std::make_shared<Pop>(stack, labels, functions)},
                {parser::Tokens::PUSHR, std::make_shared<PushR>(stack, labels, functions)},
                {parser::Tokens::POPR,  std::make_shared<PopR>(stack, labels, functions)},
                {parser::Tokens::ADD,   std::make_shared<Sum>(stack, labels, functions)},
                {parser::Tokens::SUB,   std::make_shared<Sub>(stack, labels, functions)},
                {parser::Tokens::MUL,   std::make_shared<Mul>(stack, labels, functions)},
                {parser::Tokens::DIV,   std::make_shared<Div>(stack, labels, functions)},
                {parser::Tokens::IN,    std::make_shared<In>(stack, labels, functions)},
                {parser::Tokens::OUT,   std::make_shared<Out>(stack, labels, functions)},
                {parser::Tokens::JMP,   std::make_shared<Jmp>(stack, labels, functions)},
                {parser::Tokens::JEQ,   std::make_shared<Jeq>(stack, labels, functions)},
                {parser::Tokens::JNE,   std::make_shared<Jne>(stack, labels, functions)},
                {parser::Tokens::JA,    std::make_shared<Ja>(stack, labels, functions)},
                {parser::Tokens::JAE,   std::make_shared<Jae>(stack, labels, functions)},
                {parser::Tokens::JB,    std::make_shared<Jb>(stack, labels, functions)},
                {parser::Tokens::JBE,   std::make_shared<Jbe>(stack, labels, functions)},
                {parser::Tokens::CALL,  std::make_shared<Call>(stack, labels, functions)}
        };
    }

    void Emulator::preprocess() {
        parser::Token token;
        std::string cur_label;
        token = deserializer.deserialize();
        while (token.type != parser::Tokens::END) {
            if (token.type == parser::Tokens::LABEL) {
                labels->at(token.value) = instructions.size() - 1;
                cur_label = token.value;
            } else if (token.type == parser::Tokens::RET) {
                for (unsigned long i = labels->at(cur_label); i < instructions.size(); i++) {
                    functions->at(cur_label).emplace_back(instructions[i]);
                }
                for (int i = instructions.size(); i >= labels->at(cur_label); i--) {
                    instructions.pop_back();
                }
                labels->erase(cur_label);
                functions->at(cur_label).emplace_back(token);
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


    void Push::execute(const std::string &value, int &ind) {
        long long val = std::stoll(value);
        stack->push(val);
    }

    Operation::Operation(std::shared_ptr<lib::Stack<long long int>> stack,
                         std::shared_ptr<std::unordered_map<std::string, unsigned long>> labels,
                         std::shared_ptr<std::unordered_map<std::string, std::vector<parser::Token>>> functions) {
        stack = stack;
        labels = labels;
        functions = functions;
    }


    void Pop::execute(const std::string &value, int &ind) {
        stack->pop();

    }

    void PushR::execute(const std::string &value, int &ind) {

    }

    void PopR::execute(const std::string &value, int &ind) {

    }

    void Sum::execute(const std::string &value, int &ind) {
        long long res = stack->pop() + stack->pop();
        stack->push(res);
    }

    void Sub::execute(const std::string &value, int &ind) {
        long long res = stack->pop() - stack->pop();
        stack->push(res);
    }

    void Mul::execute(const std::string &value, int &ind) {
        long long res = stack->pop() * stack->pop();
        stack->push(res);
    }

    void Div::execute(const std::string &value, int &ind) {
        long long res = stack->pop() / stack->pop();
        stack->push(res);
    }

    void In::execute(const std::string &value, int &ind) {
        long long in;
        std::cin >> in;
        stack->push(in);
    }

    void Out::execute(const std::string &value, int &ind) {
        std::cout << stack->pop() << std::endl;
    }

    void Jmp::execute(const std::string &value, int &ind) {
        ind = labels->at(value);
    }

    void Jeq::execute(const std::string &value, int &ind) {
        if (stack->pop() == stack->pop())
            ind = labels->at(value);
    }

    void Jne::execute(const std::string &value, int &ind) {
        if (stack->pop() != stack->pop())
            ind = labels->at(value);
    }

    void Ja::execute(const std::string &value, int &ind) {
        if (stack->pop() > stack->pop()) {
            ind = labels->at(value);
        }
    }

    void Jae::execute(const std::string &value, int &ind) {
        if (stack->pop() >= stack->pop()) {
            ind = labels->at(value);
        }
    }

    void Jb::execute(const std::string &value, int &ind) {
        if (stack->pop() < stack->pop()) {
            ind = labels->at(value);
        }
    }

    void Jbe::execute(const std::string &value, int &ind) {
        if (stack->pop() <= stack->pop()) {
            ind = labels->at(value);
        }
    }

    void Call::execute(const std::string &value, int &ind) {

    }


}