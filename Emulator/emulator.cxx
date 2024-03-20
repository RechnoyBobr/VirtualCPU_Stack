#include "parser/include/parser.h"
#include "preprocessor/include/preprocessor.h"
#include <memory>
#include "emulator.h"

namespace emu {
    Emulator::Emulator(const std::string &f_path, const std::string &s_path) : preprocessor(
            preproc::Preprocessor(f_path, s_path)), deserializer(s_path) {
        operations = {
                {parser::Tokens::PUSH,  std::make_shared<op::Push>()},
                {parser::Tokens::POP,   std::make_shared<op::Pop>()},
                {parser::Tokens::PUSHR, std::make_shared<op::PushR>()},
                {parser::Tokens::POPR,  std::make_shared<op::PopR>()},
                {parser::Tokens::ADD,   std::make_shared<op::Sum>()},
                {parser::Tokens::SUB,   std::make_shared<op::Sub>()},
                {parser::Tokens::MUL,   std::make_shared<op::Mul>()},
                {parser::Tokens::DIV,   std::make_shared<op::Div>()},
                {parser::Tokens::IN,    std::make_shared<op::In>()},
                {parser::Tokens::OUT,   std::make_shared<op::Out>()}
        };
    }


    void Emulator::preprocess() {
        parser::Token token;
        std::string cur_label;
        token = deserializer.deserialize();
        while (token.type != parser::Tokens::END) {
            if (token.type == parser::Tokens::LABEL) {
                cpu_memory.labels[token.value] = cpu_memory.instructions.size();
                cur_label = token.value;
            } else if (token.type == parser::Tokens::RET) {
                for (unsigned long i = cpu_memory.labels[cur_label]; i < cpu_memory.instructions.size(); i++) {
                    cpu_memory.functions[cur_label].emplace_back(cpu_memory.instructions[i]);
                }
                for (int i = cpu_memory.instructions.size(); i > cpu_memory.labels[cur_label]; i--) {
                    cpu_memory.instructions.pop_back();
                }
                cpu_memory.labels.erase(cur_label);
                cpu_memory.functions[cur_label].emplace_back(token);
            } else {
                cpu_memory.instructions.emplace_back(token);
            }
            token = deserializer.deserialize();

        }
    }

    void Emulator::run() {
        preprocessor.process_file();
        preprocessor.serialize();
        this->preprocess();
        this->execute(cpu_memory.instructions);
    }

    void Emulator::execute(std::vector<parser::Token> ins) {
        int ind = 0;
        while (ind < ins.size()) {
            switch (ins[ind].type) {
                case parser::Tokens::CALL:
                    this->execute(cpu_memory.functions[ins[ind].value]);
                    ind++;
                    continue;
                case parser::Tokens::JMP:
                    if (!has_label(ins, ins[ind].value)) {
                        return;
                    }
                    ind = cpu_memory.labels[ins[ind].value];
                    continue;
                case parser::Tokens::JEQ:
                    if (cpu_memory.stack.pop() == cpu_memory.stack.top()) {
                        if (!has_label(ins, ins[ind].value)) {
                            return;
                        }
                        ind = cpu_memory.labels[ins[ind].value];
                    } else {
                        ind++;
                    }
                    continue;
                case parser::Tokens::JNE:
                    if (cpu_memory.stack.pop() != cpu_memory.stack.top()) {
                        if (!has_label(ins, ins[ind].value)) {
                            return;
                        }
                        ind = cpu_memory.labels[ins[ind].value];
                    } else {
                        ind++;
                    }
                    continue;
                case parser::Tokens::JA:
                    if (cpu_memory.stack.pop() > cpu_memory.stack.top()) {
                        if (!has_label(ins, ins[ind].value)) {
                            return;
                        }
                        ind = cpu_memory.labels[ins[ind].value];
                    } else {
                        ind++;
                    }
                    continue;
                case parser::Tokens::JAE:
                    if (cpu_memory.stack.pop() >= cpu_memory.stack.top()) {
                        if (!has_label(ins, ins[ind].value)) {
                            return;
                        }
                        ind = cpu_memory.labels[ins[ind].value];
                    } else {
                        ind++;
                    }
                    continue;
                case parser::Tokens::JB:
                    if (cpu_memory.stack.pop() < cpu_memory.stack.top()) {
                        if (!has_label(ins, ins[ind].value)) {
                            return;
                        }
                        ind = cpu_memory.labels[ins[ind].value];
                    } else {
                        ind++;
                    }
                    continue;
                case parser::Tokens::JBE:
                    if (cpu_memory.stack.pop() <= cpu_memory.stack.top()) {
                        if (!has_label(ins, ins[ind].value)) {
                            return;
                        }
                        ind = cpu_memory.labels[ins[ind].value];
                    } else {
                        ind++;
                    }
                    continue;
            }
            if (ins[ind].type != parser::Tokens::RET) {
                operations[ins[ind].type]->execute(cpu_memory, ins[ind].value);
            }
            ind++;
        }
    }

    bool Emulator::has_label(const std::vector<parser::Token> &ins, const std::string &a) {
        for (auto &i: ins) {
            if ((i.type == parser::Tokens::JMP || i.type == parser::Tokens::JA || i.type == parser::Tokens::JAE ||
                 i.type == parser::Tokens::JB || i.type == parser::Tokens::JBE || i.type == parser::Tokens::JNE ||
                 i.type == parser::Tokens::JEQ) && i.value == a) {
                return true;
            }
        }
        return false;
    }


}