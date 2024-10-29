#pragma once

#include "Enum.hpp"
#include "DataSchema.hpp"
#include <tuple>
#include <optional>
#include <SFML/Network.hpp>
class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
    void connectToServer(const std::string& address = "127.0.0.1", unsigned short port = 54000);

    template<typename T, typename K>
    K sendRequest(RequestType type, std::optional<T> data);
    void receiveUpdates();
private:
    
    std::pair<size_t, std::vector<Player>> playerJoinHandle(const std::string& username);
    size_t receivePlayerCount();
    std::vector<Player> receivePlayers(size_t playerNum);
    sf::UdpSocket m_socket{};
    sf::IpAddress m_serverAddress{"127.0.0.1"};
    unsigned short m_port{ 54000 };
};


template<typename T, typename K>
K NetworkManager::sendRequest(RequestType type, std::optional<T> data)
{
    switch (type)
    {
    case CONNECT:
        break;
    case PLAYER_JOIN:
        if (data.has_value())
        {
            return playerJoinHandle(data.value());
        }
        return K{};
    case PLAYER_LEFT:
        break;
    case PLAYER_MOVE:
        break;
    case PLAYER_ATTACK:
        break;
    default:
        return K{};
        break;
    }
}