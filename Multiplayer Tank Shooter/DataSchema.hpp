#pragma once

#include "Enum.hpp"
#include <cstdint>
#include <SFML/Network/Packet.hpp>
#include "extra_sf_packet_op.hpp"
#include <cmath>
struct Position 
{
    int32_t x = 0;
    int32_t y = 0;
};
struct DirectionVector
{
    double x;
    double y;
    DirectionVector normalize() const {
        double magnitude = std::sqrt(x * x + y * y); 

        if (magnitude == 0) {
            return { 0, 0 }; 
        }

        return { x / magnitude, y / magnitude };
    }
};

struct Player
{
    sf::Uint64 id{ 0 };
    std::string name{};
    Position pos{};
    Direction direction{};
    float scale{};
    double traverseAngle{};
    sf::Int64 point{};
    bool isActive{};
    Player() = default;
    Player(sf::Uint64 id) : id{ id }
    {}
   
};
struct BulletData
{
    sf::Uint64 playerId{ 0 };
    Position origin{};
    DirectionVector direction{};
    Position currentPos{};
    bool isActive{ false };

};

sf::Packet& operator <<(sf::Packet& packet, const BulletData& bullet);


sf::Packet& operator >>(sf::Packet& packet, BulletData& bullet);




//struct Player
//{
//    sf::Uint64 id{ 999999 };
//    std::string ip{};
//    unsigned short port{ 9 };
//    std::string name{};
//    Position pos{};
//    Direction direction{};
//    float scale{};
//    float traverseAngle{};
//    sf::Int64 point{};
//    bool isActive{ false };
//    Player() = default;
//    Player(sf::Uint64 id) : id{ id }
//    {}
//};
sf::Packet& operator <<(sf::Packet& packet, const Player& player);


sf::Packet& operator >>(sf::Packet& packet, Player& player);

struct PlayerJoinPack
{
    sf::Uint64 player_id;
    std::vector<Player> players;
    std::vector<BulletData> bullets;
};