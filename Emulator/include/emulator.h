#pragma once

#include <unordered_map>
#include "../preprocessor/include/preprocessor.h"
#include "../parser/include/parser.h"
#include <string>

namespace emu {


    class Operation {
    public:
        Operation() = default;

        virtual void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) = 0;
    };

    class Sum : public Operation {
    public:

        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class Sub : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class Mul : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class Div : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class In : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class Out : public Operation {
    public:

        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class Push : public Operation {
    public :
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class Pop : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class PushR : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };

    class PopR : public Operation {
    public:
        void execute(preproc::Preprocessor &preprocessor, long long a, const char* reg) override;
    };


    class Emulator {
    private:
        preproc::Preprocessor preprocessor;
        parser::Parser parser;
    public:
        explicit Emulator(const char *f_path);

        void process_file();

    };


}