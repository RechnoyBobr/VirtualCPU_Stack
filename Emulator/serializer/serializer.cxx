#include "serializer.h"

#include <fstream>
#include <iostream>

namespace serializer {
    Serializer::Serializer(const std::string &f_path) : path(f_path) {
        stream.open(path, std::ios::out);
        if (!stream.is_open()) {
            throw SerializerError();
        }
    }

    void Serializer::serialize(const parser::Token &token) {
        if (!stream.is_open()) {
            throw SerializerError();
        }
        const auto pos = stream.tellp();
        const auto len = static_cast<u_int32_t> (token.value.size());
        stream.write(reinterpret_cast<const char *>(&len), sizeof(len));
        stream.write(token.value.data(), len);

    }


    Serializer::~Serializer() {
        stream.close();
    }


    const char *serializer::SerializerError::what() const noexcept {
        return "There is a problem with serialization. Please try again.";
    }

    Deserializer::~Deserializer() {
        stream.close();
    }

    parser::Token Deserializer::deserialize() {
        if (!stream.is_open()) {
            throw SerializerError();
        }
        parser::Token token;
        stream.read(reinterpret_cast<char *>(&token.type), sizeof(parser::Tokens));
        u_int32_t len;
        stream.read(reinterpret_cast<char *>(&len), sizeof(len));
        token.value.resize(len);
        stream.read(reinterpret_cast<char *>(&token.value), len);
        return token;
    }

    Deserializer::Deserializer(const std::string &f_path) : path(f_path) {
        stream.open(path, std::ios::in);

    }
}