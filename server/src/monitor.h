#pragma once

#include <unordered_map>
#include <mutex>

#include "room.h"
#include "errors.h"

class Monitor {
    std::unordered_map<std::string, Room> rooms;
    mutable std::mutex roomsMtx;

public:
    static Monitor &instance();

    JoinErr addMate(const std::string &roomId, const Mate &mate);
    LeaveErr removeMate(const std::string &roomId, const std::string &mateId);
    LeaveErr removeRoom(const std::string &roomId);
};