#include "DataSchema.hpp"
inline sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
    return packet << player.id << player.name << player.pos.x << player.pos.y << player.direction << player.scale << player.traverseAngle << player.point;
}

inline sf::Packet& operator >>(sf::Packet& packet, Player& player)
{
    return packet >> player.id >> player.name >> player.pos.x >> player.pos.y >> player.direction >> player.scale >> player.traverseAngle >> player.point;
}