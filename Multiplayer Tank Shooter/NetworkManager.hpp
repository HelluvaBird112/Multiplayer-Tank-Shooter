#pragma once
#include "Tank.hpp"

#include "Enum.hpp"
#include "DataSchema.hpp"
#include "Bullet.hpp"
#include <SFML/Network.hpp>
#include <mutex>

#include <cstdlib>
#include <ctime>

class Tank;
class NetworkManager 
{
public:
    NetworkManager();
    ~NetworkManager();
    void connectToServer(const std::string& address = "127.0.0.1", unsigned short port = 54000);

   /* template<typename T, typename K>
    K sendRequest(RequestType type, std::optional<T> data);*/
    void receiveUpdates(std::vector<Tank>& tanks, std::vector<Bullet>& bullets);
    PlayerJoinPack playerJoinHandle(const std::string& username);
    bool playerMoveHandle(const Direction direction, sf::Uint64 playerId);
    bool  player_rotate_weapon_handle(double traverseAngle, sf::Uint64 playerId);
    bool player_shot_handle(sf::Uint64 playerId, DirectionVector direction);

private:
    

    std::pair<sf::Uint64, sf::Uint64> receivePlayerCountAndId();
    std::vector<Player> receivePlayers() ;
    std::vector<BulletData> receiveBullets();
    void handlePlayerMoveResponse(sf::Packet& packet, std::vector<Tank>& tanks);
    void handlePlayerRotateWeapon(sf::Packet& packet, std::vector<Tank>& tanks);
    void handlePlayerShotResponse(sf::Packet& packet, std::vector<Bullet>& bullets);
    sf::UdpSocket m_socket{};
    sf::UdpSocket m_receiveSocket{};
    unsigned short m_receivePort{};
    sf::IpAddress m_serverAddress{"127.0.0.1"};
    
    std::mutex mt{};
    unsigned short m_port{ 54000 };
};




//template<typename T, typename K>
//K NetworkManager::sendRequest(RequestType type, std::optional<T> data)
//{
//    switch (type)
//    {
//    case CONNECT:
//        break;
//    case PLAYER_JOIN:
//        if (data.has_value()) {
//            return playerJoinHandle(data.value());
//        }
//        break;
//    case PLAYER_LEFT:
//        break;
//    case PLAYER_MOVE:
//        if (data.has_value()) {
//            return playerMoveHandle(data.value());
//        }
//        break;
//    case PLAYER_ATTACK:
//        break;
//    default:
//        return K{};
//    }
//
//    return K{};
//}