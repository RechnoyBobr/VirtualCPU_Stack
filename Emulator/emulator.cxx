#include "parser/include/parser.h"
#include "preprocessor/include/preprocessor.h"
#include <memory>
#include "emulator.h"

namespace emu {
    Emulator::Emulator(const std::string &f_path, const std::string &s_path) : preprocessor(
            preproc::Preprocessor(f_path, s_path)), deserializer(s_path) {
        operations = {
                {parser::Tokens::PUSH,  std::make_shared<Push>(stack)},
                {parser::Tokens::POP,   std::make_shared<Pop>(stack)},
                {parser::Tokens::PUSHR, std::make_shared<PushR>(stack)},
                {parser::Tokens::POPR,  std::make_shared<PopR>(stack)},
                {parser::Tokens::ADD,   std::make_shared<Sum>(stack)},
                {parser::Tokens::SUB,   std::make_shared<Sub>(stack)},
                {parser::Tokens::MUL,   std::make_shared<Mul>(stack)},
                {parser::Tokens::DIV,   std::make_shared<Div>(stack)},
                {parser::Tokens::IN,    std::make_shared<In>(stack)},
                {parser::Tokens::OUT,   std::make_shared<Out>(stack)},
                {parser::Tokens::JMP,   std::make_shared<Jmp>(stack)},
                {parser::Tokens::JEQ,   std::make_shared<Jeq>(stack)},
                {parser::Tokens::JNE,   std::make_shared<Jne>(stack)},
                {parser::Tokens::JA,    std::make_shared<Ja>(stack)},
                {parser::Tokens::JAE,   std::make_shared<Jae>(stack)},
                {parser::Tokens::JB,    std::make_shared<Jb>(stack)},
                {parser::Tokens::JBE,   std::make_shared<Jbe>(stack)},
                {parser::Tokens::CALL,  std::make_shared<Call>(stack)},
                {parser::Tokens::RET,   std::make_shared<Ret>(stack)}
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
                for (int i = labels[cur_label]; i < instructions.size(); i++) {
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


    Operation::Operation(std::shared_ptr<lib::Stack<long long int>>
                         stack) : stack(std::move(stack)) {

    }

    void Push::execute(const std::string &value) {
        long long val = std::stoll(value);
        stack->push(val);
    }

    void Pop::execute(const std::string &value) {
        stack->pop();
    }

    void PushR::execute(const std::string &value) {

    }

    void PopR::execute(const std::string &value) {

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

    void Jmp::execute(const std::string &value) {

    }

    void Jeq::execute(const std::string &value) {

    }

    void Jne::execute(const std::string &value) {

    }

    void Ja::execute(const std::string &value) {

    }

    void Jae::execute(const std::string &value) {

    }

    void Jb::execute(const std::string &value) {

    }

    void Jbe::execute(const std::string &value) {

    }

    void Call::execute(const std::string &value) {

    }

    void Ret::execute(const std::string &value) {

    }


}