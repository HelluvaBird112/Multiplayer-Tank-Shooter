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
    int64_t id{ 0 };
    char ip[15]{ 0 };
    unsigned short port{};
    char name[32]{};
    Position pos{};
    Direction direction{};
    float scale{};
    float traverseAngle{};
    int64_t point{};
    bool isActive{ false };
    Player() = default;
    Player(int64_t id) : id{ id }
    {}
    static consteval int getSerializeSize() noexcept
    {
        return sizeof(id) + sizeof(ip) + sizeof(port) + sizeof(name) + sizeof(pos)
            + sizeof(direction) + sizeof(scale) + sizeof(traverseAngle) + sizeof(point) + sizeof(isActive);
    }

    void serialize(char* buffer) const noexcept
    {
        std::size_t offset = 0;

        std::memcpy(buffer + offset, &id, sizeof(id));
        offset += sizeof(id);

        std::memcpy(buffer + offset, ip, sizeof(ip));
        offset += sizeof(ip);

        std::memcpy(buffer + offset, &port, sizeof(port));
        offset += sizeof(port);

        std::memcpy(buffer + offset, name, sizeof(name));
        offset += sizeof(name);

        std::memcpy(buffer + offset, &pos, sizeof(pos));
        offset += sizeof(pos);

        std::memcpy(buffer + offset, &direction, sizeof(direction));
        offset += sizeof(direction);

        std::memcpy(buffer + offset, &scale, sizeof(scale));
        offset += sizeof(scale);

        std::memcpy(buffer + offset, &traverseAngle, sizeof(traverseAngle));
        offset += sizeof(traverseAngle);

        std::memcpy(buffer + offset, &point, sizeof(point));
        offset += sizeof(point);

        std::memcpy(buffer + offset, &isActive, sizeof(isActive));
    }

    void deserialize(const char* buffer) noexcept
    {
        std::size_t offset = 0;

        std::memcpy(&id, buffer + offset, sizeof(id));
        offset += sizeof(id);

        std::memcpy(ip, buffer + offset, sizeof(ip));
        offset += sizeof(ip);

        std::memcpy(&port, buffer + offset, sizeof(port));
        offset += sizeof(port);

        std::memcpy(name, buffer + offset, sizeof(name));
        offset += sizeof(name);

        std::memcpy(&pos, buffer + offset, sizeof(pos));
        offset += sizeof(pos);

        std::memcpy(&direction, buffer + offset, sizeof(direction));
        offset += sizeof(direction);

        std::memcpy(&scale, buffer + offset, sizeof(scale));
        offset += sizeof(scale);

        std::memcpy(&traverseAngle, buffer + offset, sizeof(traverseAngle));
        offset += sizeof(traverseAngle);

        std::memcpy(&point, buffer + offset, sizeof(point));
        offset += sizeof(point);

        std::memcpy(&isActive, buffer + offset, sizeof(isActive));
    }
};


