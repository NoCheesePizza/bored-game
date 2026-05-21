#include "room.h"

JoinErr Room::addMate(const Mate &mate) {
    std::lock_guard lock(matesMtx);
    if (mates.count(mate.id)) {
        return JoinErr::PLAYER_EXISTS;
    }
    mates[mate.id] = mate;
    return JoinErr::NO_ERR;
}

LeaveErr Room::removeMate(const std::string &id) {
    std::lock_guard lock(matesMtx);
    auto mate = mates.find(id);
    if (mate == mates.end()) {
        return LeaveErr::PLAYER_NOT_FOUND;
    }
    mates.erase(mate);
    return LeaveErr::NO_ERR;
}

size_t Room::getCount() const {
    std::lock_guard lock(matesMtx);
    return mates.size();
}