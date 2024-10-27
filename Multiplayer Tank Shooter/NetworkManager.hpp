#pragma once

#include "Enum.hpp"

#include <SFML/Network.hpp>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
private:
    void connectToServer();
    void connectToServer(const std::string& address, int port);
    void sendInput(InputType type);
    void receiveUpdates();
    sf::UdpSocket m_socket;
    sf::IpAddress m_serverAddress{"127.0.0.1"};
    unsigned short m_port{ 54000 };
};

