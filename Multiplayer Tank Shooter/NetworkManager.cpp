#include "NetworkManager.hpp"
#include <iostream>
#include <iomanip>

NetworkManager::NetworkManager() 
{
    m_socket.setBlocking(false);
}

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
    sf::Packet packet{};
    if (m_socket.receive(packet, m_serverAddress, m_port))
    {
        return;
    }
    RequestType reqType{};
    packet << reqType;
    switch (reqType)
    {
        case CONNECT:
            break;
        case PLAYER_JOIN:
            break;
        case PLAYER_LEFT:
            break;
        case PLAYER_MOVE:
            handlePlayerMoveResponse(packet);
            break;
        case PLAYER_ATTACK:
            break;
        case PLAYER_COUNT:
            break;
        default:
            break;
    }
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

    auto idAndNumPair = receivePlayerCountAndId();
    if (idAndNumPair.first == 0)
    {
        return {};
    }

    auto players = receivePlayers(idAndNumPair.second);
    return std::make_pair(idAndNumPair.first, players);
}

bool NetworkManager::playerMoveHandle(const Direction direction)
{
    sf::Packet packet{};
    RequestType reqType{ PLAYER_MOVE };
    packet << reqType << direction;
    if (m_socket.send(packet, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Cant send PLAYER_MOVE request to server!\n";
        return false;
    }
    return true;
}

std::pair<sf::Uint64, sf::Uint64> NetworkManager::receivePlayerCountAndId()
{
    sf::Packet packet;
    if (m_socket.receive(packet, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive number of players !!\n";
        return {};
    }

    sf::Uint64 playerNum{0};
    sf::Int8 reqType{};
    sf::Uint64 playerId{};
    std::cout << playerNum;
    if (packet >> reqType >> playerNum >> playerId)
    {
        std::cout << "playerNum : " << playerNum << "\n";
        return std::make_pair(playerId,playerNum);
    }

    std::cerr << "Invalid packet received for player count.\n";
    return {};
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
        if (packet >> players[i])
        {
            std::cout << "Player name: " << players[i].name << "\n";
            std::cout << "Player id: " << players[i].id << "\n";
        }
        else
        {
            std::cerr << "Error reading player data.\n";
        }
    }

    return players;
}

void NetworkManager::handlePlayerMoveResponse(sf::Packet& packet)
{
    sf::Uint64 playerId{};
    Position playerPos;
    packet >> playerId >> playerPos.x >> playerPos.y;

}
