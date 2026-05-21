#include "monitor.h"

Monitor &Monitor::instance() {
    static Monitor monitor;
    return monitor;
}

JoinErr Monitor::addMate(const std::string &roomId, const Mate &mate) {
    std::lock_guard lock(roomsMtx);
    return rooms[roomId].addMate(mate);
}

LeaveErr Monitor::removeMate(const std::string &roomId, const std::string &mateId) {
    std::lock_guard lock(roomsMtx);
    auto room = rooms.find(roomId);
    if (room == rooms.end()) {
        return LeaveErr::ROOM_NOT_FOUND;
    }
    return room->second.removeMate(mateId);
}

LeaveErr Monitor::removeRoom(const std::string &roomId) {
    std::lock_guard lock(roomsMtx);
    auto room = rooms.find(roomId);
    if (room == rooms.end()) {
        return LeaveErr::ROOM_NOT_FOUND;
    }
    rooms.erase(room);
    return LeaveErr::NO_ERR;
}