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

std::pair<size_t, std::vector<Player>> NetworkManager::playerJoinHandle(const std::string& username)
{
    constexpr RequestType reqType = PLAYER_JOIN;
    std::vector<char> buffer(sizeof(RequestType) + sizeof(Player::name));
    memcpy_s(buffer.data(), sizeof(RequestType), (void*)(&reqType), sizeof(RequestType));
    memcpy_s(buffer.data() + sizeof(RequestType), sizeof(Player::name), (void*)(username.c_str()), sizeof(Player::name));


    if (m_socket.send(buffer.data(), sizeof(buffer), m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Can't send join request to server !!\n";
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
    
    memcpy(&playerNum, numPlayerPacket.data()+1, sizeof(playerNum));
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
    std::cout << "Receive bytes: " << receivedBytes << " Need Bytes: " << playerNum * sizeof(Player) << "\n";
    for (const Player& player : playerContainer)
    {
        std::cout << " Player name: " << player.name << "\n";
        std::cout << "Player " << " id: " << player.id  << " ip: " << player.ip << " port:" << player.port << "\n";
    }
    return playerContainer;
}