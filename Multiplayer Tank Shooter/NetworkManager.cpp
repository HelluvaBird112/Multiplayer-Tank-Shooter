#include "NetworkManager.hpp"
#include <iostream>

NetworkManager::NetworkManager()
{
    connectToServer();
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
}

std::tuple<int64_t, std::vector<Player>> NetworkManager::playerJoinHandle()
{
    if (!NetworkManager::sendRequestToServer(PLAYER_JOIN))
    {
        return {};
    }

    size_t playerNum = NetworkManager::receivePlayerCount();
    if (playerNum == 0)
    {
        return {};
    }

    auto players = receivePlayers(playerNum);
    return std::make_tuple(playerNum, players);
}

bool NetworkManager::sendRequestToServer(RequestType requestType)
{
    if (m_socket.send(reinterpret_cast<char*>(&requestType), sizeof(requestType), m_serverAddress, m_port) != sf::Socket::Done) {
        std::cerr << "Failed to send request" << std::endl;
        return false;
    }
    return true;
}

size_t NetworkManager::receivePlayerCount()
{
    size_t playerNum{};
    auto numPlayerPacket = std::make_unique<char[]>(sizeof(playerNum));
    std::size_t receivedBytes{};

    if (m_socket.receive(numPlayerPacket.get(), sizeof(playerNum), receivedBytes, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive number of players !!\n";
        return 0;
    }

    memcpy(&playerNum, numPlayerPacket.get(), sizeof(playerNum));
    return playerNum;
}

std::vector<Player> NetworkManager::receivePlayers(size_t playerNum)
{
    auto playerContainer = std::vector<Player>(playerNum);
    auto playerContainerPacket = std::make_unique<char[]>(playerNum * sizeof(Player));
    std::size_t receivedBytes{};

    if (m_socket.receive(playerContainerPacket.get(), playerNum * sizeof(Player), receivedBytes, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive player data !!\n";
        return {};
    }

    memcpy(playerContainer.data(), playerContainerPacket.get(), playerNum * sizeof(Player));
    return playerContainer;
}