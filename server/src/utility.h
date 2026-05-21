#include <string>
#pragma once

#include <random>

#define VALIDATE_KEY(json, key, type, def) (json).isMember(key) && (json)[key].is##type() ? (json)[key].as##type() : def

namespace uti {
    inline std::string generateId(size_t length = 32) {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, chars.size() - 1);
        std::string id;

        for (size_t i = 0; i < length; ++i) {
            id += chars[dis(gen)];
        }
        return id;
    }
}