#pragma once
#include <SFML/Network/Packet.hpp>
enum Direction : sf::Uint8 
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

enum  RequestType : sf::Uint8
{
    CONNECT,
    PLAYER_JOIN,
    PLAYER_LEFT,
    PLAYER_MOVE,
    PLAYER_ATTACK,
    PLAYER_COUNT,
    PLAYER_ROTATE_WEAPON,
    PLAYER_SHOT
};

enum ResponseType : char
{};

enum TankType : int8_t
{
    TANK_TYPE_1,
    TANK_TYPE_2
};