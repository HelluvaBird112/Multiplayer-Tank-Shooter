#include "DataSchema.hpp"


sf::Packet& operator <<(sf::Packet& packet, const Player& player)
{
    return packet << player.id << player.name << player.pos.x << player.pos.y << player.direction << player.scale << player.traverseAngle << player.point << player.isActive;
}

sf::Packet& operator >>(sf::Packet& packet, Player& player)
{
    return packet >> player.id >> player.name >> player.pos.x >> player.pos.y >> player.direction >> player.scale >> player.traverseAngle >> player.point >> player.isActive;
}

sf::Packet& operator <<(sf::Packet& packet, const BulletData& bullet)
{
    return packet << bullet.playerId << bullet.origin.x << bullet.origin.y << bullet.currentPos.x << bullet.currentPos.y << bullet.direction.x << bullet.direction.y << bullet.isActive;
}

sf::Packet& operator >>(sf::Packet& packet, BulletData& bullet)
{
    return packet >> bullet.playerId >> bullet.origin.x >> bullet.origin.y >> bullet.currentPos.x >> bullet.currentPos.y >> bullet.direction.x >> bullet.direction.y >> bullet.isActive;
}
