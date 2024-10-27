#include "Client.hpp"

Client::Client()
    : m_assetManager(std::make_shared<AssetManager>()),
    m_networkManager(std::make_shared<NetworkManager>()),
    m_audioManager(std::make_shared<AudioManager>()),
    m_menu(std::make_unique<Menu>(m_assetManager, m_networkManager, m_audioManager)),
    m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(800,600), "Menu"))
{
   

}

Client::~Client()
{
}

bool Client::run()
{
    return false;
}
