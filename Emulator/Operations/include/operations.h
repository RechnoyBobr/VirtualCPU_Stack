#pragma once

#include "../../parser/include/parser.h"
#include <memory>
#include "../../Memory/include/emu_memory.h"

namespace op {
    class Operation {
    protected:
        std::shared_ptr<memo::Memory> memory;
    public:
        Operation() = default;

        virtual void execute(memo::Memory &memory,const std::string &value) = 0;
    };

    class Sum : public Operation {
    public:
        
        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class Sub : public Operation {
    public:

        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class Mul : public Operation {
    public:
        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class Div : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class Push : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class Pop : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class PushR : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class PopR : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class In : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

    class Out : public Operation {
    public:


        void execute(memo::Memory &memory,const std::string &value) override;
    };

}
