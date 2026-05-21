#pragma once

#include <string>
#include <json/json.h>

struct Mate {
    int score = 0;
    bool isWinner = false; // whether won last round for fire emoji
    std::string name;
    std::string id;

    static Mate fromJson(const Json::Value &json);
};