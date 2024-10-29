#include "NetworkManager.hpp"
#include <iostream>
#include <iomanip>

NetworkManager::NetworkManager() {}

NetworkManager::~NetworkManager() {}

void NetworkManager::connectToServer(const std::string& address, unsigned short port)
{
    m_serverAddress = sf::IpAddress(address);
    m_port = port;
    const char message[] = "Ping from client!!";
    if (m_socket.send(message, sizeof(message), m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't connect to server!!\n";
    }
}

void NetworkManager::receiveUpdates()
{
    // Implement receiving updates from the server if needed
}

std::pair<size_t, std::vector<Player>> NetworkManager::playerJoinHandle(const std::string& username)
{
    sf::Packet packet;
    constexpr RequestType reqType = RequestType::PLAYER_JOIN; 
    packet << reqType << username;

    if (m_socket.send(packet, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't send join request to server !!\n";
        return {};
    }

    size_t playerNum = receivePlayerCount();
    if (playerNum == 0)
    {
        return {};
    }

    auto players = receivePlayers(playerNum);
    return std::make_pair(playerNum, players);
}

size_t NetworkManager::receivePlayerCount()
{
    sf::Packet packet;
    if (m_socket.receive(packet, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive number of players !!\n";
        return 0;
    }

    size_t playerNum;
    if (packet >> playerNum)
    {
        std::cout << "playerNum : " << playerNum << "\n";
        return playerNum;
    }

    std::cerr << "Invalid packet received for player count.\n";
    return 0;
}

std::vector<Player> NetworkManager::receivePlayers(size_t playerNum) 
{
    sf::Packet packet;
    if (m_socket.receive(packet, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive player data !!\n";
        return {};
    }

    std::vector<Player> players(playerNum);
    for (size_t i = 0; i < playerNum; ++i)
    {
        Player player; 
        if (packet >> player.id >> player.name >> player.ip >> player.port) 
        {
            players[i] = player; 
            std::cout << "Player name: " << player.name << "\n";
            std::cout << "Player id: " << player.id << " ip: " << player.ip << " port: " << player.port << "\n";
        }
        else
        {
            std::cerr << "Error reading player data.\n";
        }
    }

    return players;
}