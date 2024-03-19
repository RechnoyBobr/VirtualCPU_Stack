#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../../parser/include/parser.h"

namespace serializer {
    class SerializerError : std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class Serializer {
    private:
        std::ofstream stream;
        std::string path;
    public:
        explicit Serializer(const std::string &f_path);


        void serialize(const parser::Token &token);

    };
    class Deserializer {
    private:
        std::ifstream stream;
        std::string path;
    public:

        explicit Deserializer(const std::string &f_path);

        parser::Token deserialize();

    };
}