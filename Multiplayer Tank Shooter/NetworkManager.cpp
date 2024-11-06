#include "NetworkManager.hpp"
#include <iostream>
#include <iomanip>
#include "GamePanel.hpp"

void gen_req_header_with_credentical(sf::Packet& packet, RequestType reqType, sf::Uint64 playerId)
{
    packet << reqType << playerId;
}

NetworkManager::NetworkManager()
{
    m_socket.setBlocking(true);  

    std::srand(static_cast<unsigned int>(std::time(0)));
    auto randomPort{ std::rand() % 10001 + 50000 };
    while (m_receiveSocket.bind(randomPort, m_serverAddress) != sf::Socket::Done)
    {
        std::cout << "Cant bind receive port to port: " << randomPort << "!!\n";
    }
    std::cout << "Bind client to port: " << randomPort << "\n";
    m_receivePort = randomPort;
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

void NetworkManager::receiveUpdates(std::vector<Tank>& tanks, std::vector<Bullet>& bullets)
{
    sf::Packet packet{};

    while (m_receiveSocket.receive(packet, m_serverAddress, m_port) == sf::Socket::Done)
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
        {
            sf::Uint64 newPlayerId{};
            Player player{};
            packet >> newPlayerId >> player;
            std::cout << "Player has name: " << player.name << " and id: " << player.id << " connected!\n";

            tanks[newPlayerId].m_player = player;
            break;
        }
        case PLAYER_LEFT:
            std::cout << "Player left.\n";
            break;
        case PLAYER_MOVE:
            handlePlayerMoveResponse(packet, tanks);
            break;
        case PLAYER_ATTACK:
            std::cout << "Player attack event received.\n";
            break;
        case PLAYER_COUNT:
            std::cout << "Player count event received.\n";
            break;
        case PLAYER_ROTATE_WEAPON:
            handlePlayerRotateWeapon(packet, tanks);
            break;
        case PLAYER_SHOT:
            handlePlayerShotResponse(packet, bullets);
            break;
        default:
            std::cerr << "Unknown request type received.\n";
            break;
        }
    }
}

PlayerJoinPack NetworkManager::playerJoinHandle(const std::string& username)
{
    std::cout << "receive port in playerJoinHandle is: " << m_receivePort << "!\n";
    sf::Packet packet;
    constexpr RequestType reqType = RequestType::PLAYER_JOIN;
    packet << reqType << username << m_receivePort;

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
    sf::Packet playerIdPacket{};
    sf::Uint64 playerId{};
    if (m_receiveSocket.receive(playerIdPacket, m_serverAddress, m_port) != sf::Socket::Done)
    {
        std::cerr << "Cant receive player id.\n";
        return {};
    }
    playerIdPacket >> playerId;
    auto players = receivePlayers();
    auto bullets = receiveBullets();
    return PlayerJoinPack{playerId,players,bullets};
}

bool NetworkManager::playerMoveHandle(const Direction direction, sf::Uint64 playerId)
{
    sf::Packet packet{};
    RequestType reqType{ PLAYER_MOVE };
    gen_req_header_with_credentical(packet, reqType, playerId);
    packet << direction;
    auto status = m_socket.send(packet, sf::IpAddress("127.0.0.1"), 54000);
    //std::cout << "In move hanlde: packet size: " << packet.getDataSize() << " bytes to address: " << "127.0.0.1" << " port: " << 54000 << "\n";
    if (status != sf::Socket::Done)
    {
        std::cout << "status: " << status << "\n";
        std::cerr << "Can send MOVE REQUEST To server\n";
        return false;
    }
    return true;
}

bool NetworkManager::player_rotate_weapon_handle(double traverseAngle, sf::Uint64 playerId)
{
    sf::Packet packet{};
    RequestType reqType{ PLAYER_ROTATE_WEAPON };
    packet << reqType << playerId << traverseAngle;
    //std::cout << "traverseAngle: " << traverseAngle << "\n";
    auto status = m_socket.send(packet, sf::IpAddress("127.0.0.1"), 54000);
    if (status != sf::Socket::Done)
    {
        std::cout << "status: " << status << "\n";
        std::cerr << "Can send PLAYER_ROTATE_WEAPON To server\n";
        return false;
    }
    return true;
}

bool NetworkManager::player_shot_handle(sf::Uint64 playerId, DirectionVector direction)
{
    sf::Packet packet{};
    RequestType reqType{ PLAYER_SHOT };
    
    packet << reqType << playerId << direction.x << direction.y;
    if (m_socket.send(packet, sf::IpAddress("127.0.0.1"), 54000) != sf::Socket::Done)
    {
        std::cerr << "Can send PLAYER_SHOT To server\n";
        return false;
    }
    return true;
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
            //std::cout << "Receive " << packet.getDataSize() << " bytes\n";
            //std::cout <<"req type: " <<reqType << "playerNum : " << playerNum << "playerId: " << playerId<< "\n";
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

        if (m_receiveSocket.receive(packet, m_serverAddress, m_port) == sf::Socket::Done)
        {
            size_t containerSize{};
            packet >> containerSize;
            std::vector<Player> players(containerSize);

            //std::cout << "PLayer container size is: " <<containerSize << "player vector Bytes receive : " << packet.getDataSize() << " bytes\n";
            Player player{};
            for (int i = 0; i < containerSize; i++)
            {
                packet >> player;
                players[i] = player;
               // std::cout << "Player name: " << player.name << "\n";
                // std::cout << "Player id: " << player.id << "\n";
                /// std::cout << "Player pos:" << player.pos.x << "\n";
            }
            return players;
          
        }
        else
        {
            std::cerr << "Cant get player container!!\n";
        }
    

        return {};
}

std::vector<BulletData> NetworkManager::receiveBullets()
{
    sf::Packet packet;

    if (m_receiveSocket.receive(packet, m_serverAddress, m_port) == sf::Socket::Done)
    {
        size_t containerSize{};
        packet >> containerSize;
        std::vector<BulletData> bullets(containerSize);

        //std::cout << "PLayer container size is: " <<containerSize << "player vector Bytes receive : " << packet.getDataSize() << " bytes\n";
        BulletData bullet{};
        for (int i = 0; i < containerSize; i++)
        {
            packet >> bullet;
            bullets[i] = bullet;
            // std::cout << "Player name: " << player.name << "\n";
             // std::cout << "Player id: " << player.id << "\n";
             /// std::cout << "Player pos:" << player.pos.x << "\n";
        }
        return bullets;

    }
    else
    {
        std::cerr << "Cant get player container!!\n";
    }


    return {};
}

void NetworkManager::handlePlayerMoveResponse(sf::Packet& packet, std::vector<Tank>& tanks)
{
    sf::Uint64 playerId{};
    Position playerPos;
    packet >> playerId >> playerPos.x >> playerPos.y;
    //std::cout << "players size: " << tanks.size() << "\n";
    if (playerId < tanks.size())
    {
        //std::cout << playerId << " move to x:" << playerPos.x << " y: " << playerPos.y << "\n";
        tanks[playerId].m_player.pos = { playerPos };
        //std::cout << "after move: x:" << tanks[playerId].m_player.pos.x << " y: " << tanks[playerId].m_player.pos.y << "\n";
    }
    else
    {
        std::cerr << "Invalid player ID received.\n";
    }
}

void NetworkManager::handlePlayerRotateWeapon(sf::Packet& packet, std::vector<Tank>& tanks)
{
    sf::Uint64 playerId{};
    double travesalAngle{};
    packet >> playerId >> travesalAngle;
    tanks[playerId].m_player.traverseAngle = travesalAngle;
    //std::cout << "Player " << tanks[playerId].m_player.name << " rotate weapon to " << travesalAngle << "\n";

}

void NetworkManager::handlePlayerShotResponse(sf::Packet& packet, std::vector<Bullet>& bullets)
{
    BulletData bulletData{};
    sf::Uint64 bulletId{ };
    packet >> bulletId >> bulletData;
    std::cout << "bullet id " << bulletId << " is ["<< bulletData.isActive<<"] and " <<" fire in x : " << bulletData.origin.x << " y : " << bulletData.origin.y << " fire!!\n";
    std::cout << "Direction: x:" << bulletData.direction.x << " y: " << bulletData.direction.y << "\n";
    bullets[bulletId].m_data = bulletData;
}
