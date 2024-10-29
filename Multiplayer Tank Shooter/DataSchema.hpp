#pragma once

#include "Enum.hpp"
#include <cstdint>
#include <SFML/Network/Packet.hpp>
#include "extra_sf_packet_op.hpp"

struct Position 
{
    int32_t x = 0;
    int32_t y = 0;
};

struct Player
{
    sf::Int64 id{ 0 };
    std::string ip{};
    unsigned short port{};
    std::string name{};
    Position pos{};
    Direction direction{};
    float scale{};
    float traverseAngle{};
    sf::Int64 point{};
    bool isActive{ false };
    Player() = default;
    Player(int64_t id) : id{ id }
    {}
};
inline sf::Packet& operator <<(sf::Packet& packet, const Player& player);


inline sf::Packet& operator >>(sf::Packet& packet, Player& player);

