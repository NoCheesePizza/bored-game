#pragma once

#include <string>
#include <unordered_map>
#include <mutex>

#include "mate.h"
#include "errors.h"

class Room {
    std::string id;
    std::unordered_map<std::string, Mate> mates;
    mutable std::mutex matesMtx; // modifiable in const methods
    // game type
    // game state
    // configs

public:
    JoinErr addMate(const Mate &mate);
    LeaveErr removeMate(const std::string &id);
    size_t getCount() const;
};