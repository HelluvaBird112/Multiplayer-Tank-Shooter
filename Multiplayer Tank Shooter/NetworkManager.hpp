#pragma once


#include <SFML/Network.hpp>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();
private:
    void connectToServer();
    void connectToServer(const std::string& address, int port);
    void sendInput();
    void receiveUpdates();
    sf::UdpSocket socket;
    sf::IpAddress serverAddress{"127.0.0.1"};
    int32_t m_port{ 54000 };
};

