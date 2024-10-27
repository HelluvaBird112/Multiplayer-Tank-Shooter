#include "NetworkManager.hpp"
#include <iostream>
NetworkManager::NetworkManager()
{
	connectToServer();
}

NetworkManager::~NetworkManager()
{}

void NetworkManager::connectToServer()
{
	char mes[100] = "Ping from client!!";
	if (m_socket.send(mes,100, m_serverAddress, m_port) != sf::Socket::Done)
	{
		std::cerr << "Cant connect to server!!\n";
	}
}

void NetworkManager::connectToServer(const std::string& address, int port)
{
}

void NetworkManager::sendInput(InputType type)
{
	switch (type)
	{
		case CONNECT:
			break;
		case JOIN:
			break;
		case MOVE:
			break;
		default:
			break;
		}
}

void NetworkManager::receiveUpdates()
{
}
