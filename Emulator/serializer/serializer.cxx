#include "serializer.h"

#include <fstream>
#include <iostream>

namespace serializer {
    Serializer::Serializer(std::string f_path) : path(std::move(f_path)) {
        stream.open(path, std::ios::out);
        if (!stream.is_open()) {
            throw SerializerError();
        }
    }

    void Serializer::close() {
        stream.close();
    }

    void Serializer::serialize(const parser::Token &token) {
        if (!stream.is_open()) {
            throw SerializerError();
        }
        const auto pos = stream.tellp();
        size_t len = (token.value.size());
        stream.write(reinterpret_cast<const char *>(&token.type), sizeof(parser::Tokens));
        stream.write(reinterpret_cast<const char *>(&len), sizeof(len));
        stream.write(token.value.data(), len);

    }


    const char *serializer::SerializerError::what() const noexcept {
        return "There is a problem with serialization. Please try again.";
    }


    parser::Token Deserializer::deserialize() {
        if (!stream.is_open()) {
            try {
                stream.open(path, std::ios::in);
            } catch (std::exception &e) {
                throw SerializerError();
            }
        }
        parser::Token token;
        stream.read(reinterpret_cast<char *>(&token.type), sizeof(parser::Tokens));
        size_t len;
        stream.read(reinterpret_cast<char *>(&len), sizeof(len));
        token.value.resize(len);
        stream.read(token.value.data(), len);
        return token;
    }

    Deserializer::Deserializer(std::string f_path) : path(std::move(f_path)) {
    }
}