#pragma once

enum Direction : char 
{
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
};

enum RequestType : char
{
    CONNECT,
    PLAYER_JOIN,
    PLAYER_LEFT,
    PLAYER_MOVE,
    PLAYER_ATTACK,
    PLAYER_COUNT
};

enum ResponseType : char
{};