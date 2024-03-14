#include "parser/include/parser.h"
#include "preprocessor/include/preprocessor.h"
#include "emulator.h"

namespace emu {
    Emulator::Emulator(const char *f_path) : parser(parser::Parser(f_path)) {};
    std::unordered_map<std::string, Operation *> operations = {
            {"ADD",   new Sum()},
            {"SUB",   new Sub()},
            {"MUL",   new Mul()},
            {"DIV",   new Div()},
            {"IN",    new In()},
            {"OUT",   new Out()},
            {"PUSH",  new Push()},
            {"POP",   new Pop()},
            {"PUSHR", new PushR()},
            {"POPR",  new PopR()}
    };

    void Emulator::process_file() {
        std::pair<std::string, std::string> res = this->parser.parseline();
        while (res.first != "BEGIN" && res.first != "\0") {
            res = this->parser.parseline();
        }
        if (res.first == "\0") {
            return;
        } else {
            while (res.first != "END" && res.first != "\0") {
                res = this->parser.parseline();
                std::optional<long long> num = this->preprocessor.parse_number(res.second);
                Operation *op = operations.at(res.first);
                if (num.has_value()) {
                    op->execute(this->preprocessor, num.value(), "");
                } else if (res.second.size() == 2) {
                    op->execute(this->preprocessor, 0, res.second.c_str());
                } else {
                    op->execute(this->preprocessor, 0, "");
                }

            }
            if (res.first != "\0") {
                throw preproc::PreprocessorError();
            }
        }

    }


    void Push::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Push(a);
    }

    void Sum::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Add();
    }

    void Sub::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Substract();
    }

    void Mul::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Multiply();
    }

    void Div::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Divide();

    }

    void Out::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Out();
    }

    void In::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.In();
    }

    void Pop::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.Pop();
    }

    void PushR::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.PushR(reg);
    }

    void PopR::execute(preproc::Preprocessor &preprocessor, long long a, const char *reg) {
        preprocessor.PopR(reg);
    }
}