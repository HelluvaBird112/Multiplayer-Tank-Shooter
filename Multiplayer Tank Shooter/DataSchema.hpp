#pragma once
#include <cstdint>
enum Direction : char {
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
};

enum TankType
{
    ONE,
    TWO,
    THREE
};

struct Position
{
    int32_t x;
    int32_t y;
};


struct Player
{
    char* name;
    Position pos;
    Direction direction;
    float scale;
    float traverseAngle;
    int64_t point;
};

struct Bullet
{
    Position pos;
    Direction direction;
};

