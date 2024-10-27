#pragma once


#include <SFML/Network.hpp>

class NetworkManager {
public:
    NetworkManager();
    void connectToServer(const std::string& address, int port);
    void sendInput();
    void receiveUpdates();

private:
    sf::TcpSocket socket;
};

