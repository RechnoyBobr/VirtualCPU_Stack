#pragma once

#include <unordered_map>
#include "../preprocessor/include/preprocessor.h"
#include "../../stack/include/stack.h"
#include "../parser/include/parser.h"
#include <utility>
#include <vector>
#include <string>

namespace emu {
    class Operation {
    protected:
        std::shared_ptr<lib::Stack<long long>> stack;
    public:
        explicit Operation(std::shared_ptr<lib::Stack<long long>> stack);

        virtual void execute(const std::string &value) = 0;
    };

    class Sum : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Sub : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Mul : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Div : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Push : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Pop : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class PushR : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class PopR : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class In : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Out : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Jmp : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Jeq : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Jne : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Ja : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Jae : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Jb : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Jbe : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Call : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };

    class Ret : public Operation {
    public:
        using Operation::Operation;

        void execute(const std::string &value) override;
    };


    class Emulator {
    private:
        preproc::Preprocessor preprocessor;
        const int stack_size = 131072;
        std::shared_ptr<lib::Stack<long long>> stack;
        std::unordered_map<parser::Tokens, std::shared_ptr<Operation>> operations;
        std::vector<parser::Token> instructions;
        std::unordered_map<std::string, unsigned long> labels;
        std::unordered_map<std::string, std::vector<parser::Token>> functions;
        serializer::Deserializer deserializer;
        std::unordered_map<std::string, long long> registers = {
                {"AX", 0},
                {"BX", 0},
                {"CX", 0},
                {"DX", 0},
                {"PC", 0}

        };
    public:
        explicit Emulator(const std::string &f_path, const std::string &s_path);

        void preprocess();

        void execute();


        void run();

    };


}