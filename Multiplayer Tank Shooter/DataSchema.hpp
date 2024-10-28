#pragma once

#include "Enum.hpp"
#include <cstdint>
#include <cstring>



struct Position 
{
    int32_t x = 0;
    int32_t y = 0;

    void serialize(char* buffer) const 
    {
        std::memcpy(buffer, this, sizeof(Position));
    }
    void deserialize(const char* buffer)
    {
        std::memcpy(this, buffer, sizeof(Position));
    }
};

struct Player 
{
    int64_t id;
    char ip[15];
    unsigned short port;
    char name[32];
    Position pos;
    Direction direction;
    float scale;
    float traverseAngle;
    int64_t point;
    bool isActive;

    static constexpr int getSerializeSize() noexcept 
    {
        return sizeof(id) + sizeof(ip) + sizeof(port) + sizeof(name) + sizeof(pos)
            + sizeof(direction) + sizeof(scale) + sizeof(traverseAngle) + sizeof(point) + sizeof(isActive);
    }

    void serialize(char* buffer) const noexcept 
    {
        std::size_t offset = 0;
        std::memcpy(buffer + offset, this, getSerializeSize());
    }

    void deserialize(const char* buffer) noexcept 
    {
        std::memcpy(this, buffer, getSerializeSize());
    }
};



