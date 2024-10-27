#pragma once
#include "AudioManager.hpp"
#include "NetworkManager.hpp"
#include "AssetManager.hpp"

#include <SFML/Graphics.hpp>

class GamePanel
{
public:
	GamePanel(std::shared_ptr<AudioManager> audioManager, std::shared_ptr<NetworkManager> networkManager, std::shared_ptr<AssetManager> assetManager);
	~GamePanel();
	bool run();
private:
	sf::RenderWindow window{ sf::VideoMode(800,600), "Game" };
	std::shared_ptr<AudioManager> m_audioManager{ nullptr };
	std::shared_ptr<NetworkManager> m_networkManager{ nullptr };
	std::shared_ptr<AssetManager> m_assetManager{ nullptr };
};