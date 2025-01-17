#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#include <jsoncpp/json/json.h>

template<typename E>
class PropertiesLoader {
public:
    static void load(const std::string &filePath) {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        Json::Value root;
        Json::CharReaderBuilder builder;
        std::string errs;

        if (!Json::parseFromStream(builder, file, &root, &errs)) {
            throw std::runtime_error("Failed to parse JSON: " + errs);
        }

        E::value = root;

        file.close();
    }
};
