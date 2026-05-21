#pragma once

enum class JoinErr {
    NO_ERR,
    PLAYER_EXISTS
};

enum class LeaveErr {
    NO_ERR,
    PLAYER_NOT_FOUND,
    ROOM_NOT_FOUND
};