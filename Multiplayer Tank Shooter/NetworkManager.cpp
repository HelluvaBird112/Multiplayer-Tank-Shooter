#include "NetworkManager.hpp"
#include <iostream>

NetworkManager::NetworkManager()
{
    //connectToServer();
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

std::pair<size_t, std::vector<Player>> NetworkManager::playerJoinHandle()
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
    return std::make_pair(playerNum, players);
}

bool NetworkManager::sendRequestToServer(RequestType requestType)
{
    std::cout << m_serverAddress << " " << m_port << "\n";
    if (m_socket.send(reinterpret_cast<char*>(&requestType), sizeof(requestType), m_serverAddress, m_port) != sf::Socket::Done) 
    {
        std::cerr << "Failed to send request" << std::endl;
        return false;
    }
    return true;
}

size_t NetworkManager::receivePlayerCount()
{
    size_t playerNum{0};
    std::vector<char> numPlayerPacket(sizeof(playerNum) + 1);
    std::size_t receivedBytes{};

    if (m_socket.receive(numPlayerPacket.data(), sizeof(playerNum) + 1, receivedBytes, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive number of players !!\n";
        return 0;
    }
    std::cout << "Receive bytes: " << receivedBytes << " Need bytes: " << sizeof(playerNum) + 1 << "\n";
    for (size_t i = 0; i < receivedBytes; ++i) {
        std::cout << "Byte " << i << ": " << static_cast<int>(numPlayerPacket[i]) << "\n";
    }
    memcpy(&playerNum, numPlayerPacket.data() + 1, sizeof(playerNum));
    std::cout << "playerNum : " << playerNum << "\n";
    return playerNum;
}

std::vector<Player> NetworkManager::receivePlayers(size_t playerNum)
{
    auto playerContainer = std::vector<Player>(playerNum);
    std::vector<char>playerContainerPacket(playerNum * sizeof(Player));
    std::size_t receivedBytes{};

    if (m_socket.receive(playerContainerPacket.data(), playerNum * sizeof(Player), receivedBytes, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't receive player data !!\n";
        return {};
    }

    memcpy(playerContainer.data(), playerContainerPacket.data(), playerNum * sizeof(Player));
    return playerContainer;
}