#include "NetworkManager.hpp"
#include <iostream>
#include <iomanip>
#include "GamePanel.hpp"

NetworkManager::NetworkManager()
{
    m_socket.setBlocking(true);  
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

void NetworkManager::receiveUpdates(std::vector<Player>& players)
{
    sf::Packet packet{};

    while (m_socket.receive(packet, m_serverAddress, m_port) == sf::Socket::Done)
    {
        RequestType reqType{};
        if (!(packet >> reqType))
        {
            std::cerr << "Failed to read request type.\n";
            return;
        }

        switch (reqType)
        {
        case CONNECT:
            std::cout << "Player connected.\n";
            break;
        case PLAYER_JOIN:
            std::cout << "Player joined.\n";
            break;
        case PLAYER_LEFT:
            std::cout << "Player left.\n";
            break;
        case PLAYER_MOVE:
            handlePlayerMoveResponse(packet, players);
            break;
        case PLAYER_ATTACK:
            std::cout << "Player attack event received.\n";
            break;
        case PLAYER_COUNT:
            std::cout << "Player count event received.\n";
            break;
        default:
            std::cerr << "Unknown request type received.\n";
            break;
        }
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
   
   /* auto idAndNumPair = receivePlayerCountAndId();
    if (idAndNumPair.second == 0)
    {
        return {};
    }*/

    auto players = receivePlayers();
    return std::make_pair(players.size(), players);
}

bool NetworkManager::playerMoveHandle(const Direction direction)
{
    sf::Packet packet{};
    RequestType reqType{ PLAYER_MOVE };
    packet << reqType << direction;
    return m_socket.send(packet, m_serverAddress, m_port) == sf::Socket::Done;
}

std::pair<sf::Uint64, sf::Uint64> NetworkManager::receivePlayerCountAndId()
{
    sf::Packet packet;
    if (m_socket.receive(packet, m_serverAddress, m_port) == sf::Socket::Done)
    {
        sf::Uint64 playerNum{ 99 };
        RequestType reqType{};
        sf::Uint64 playerId{};

        if (packet >> reqType >> playerNum >> playerId)
        {
            std::cout << "Receive " << packet.getDataSize() << " bytes\n";
            std::cout <<"req type: " <<reqType << "playerNum : " << playerNum << "playerId: " << playerId<< "\n";
            return std::make_pair(playerId, playerNum);
        }
        else
        {
            std::cerr << "Invalid packet received for player count.\n";
        }
    }
    return { 0, 0 };  
}

std::vector<Player> NetworkManager::receivePlayers()
{
    sf::Packet packet;
    std::vector<Player> players;

        if (m_socket.receive(packet, m_serverAddress, m_port) == sf::Socket::Done)
        {
            Player player{};
            if (packet >> player)
            {
                players.push_back(player);
                std::cout << "Player name: " << player.name << "\n";
                std::cout << "Player id: " << player.id << "\n";
            }
            else
            {
                std::cerr << "Error reading player data.\n";
            }
        }
    

    return players;
}

void NetworkManager::handlePlayerMoveResponse(sf::Packet& packet, std::vector<Player>& players)
{
    sf::Uint64 playerId{};
    Position playerPos;
    packet >> playerId >> playerPos.x >> playerPos.y;
    std::cout << "player id: " << playerId << " move to: x: " << playerPos.x << " y: " << playerPos.y << "\n";
    std::cout << "players size: " << players.size() << "\n";
    if (playerId < players.size())
    {
        players[playerId].pos = { playerPos };
    }
    else
    {
        std::cerr << "Invalid player ID received.\n";
    }
}