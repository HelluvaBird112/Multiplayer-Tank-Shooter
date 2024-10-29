#pragma once
#include "AudioManager.hpp"
#include "NetworkManager.hpp"
#include "AssetManager.hpp"
#include "DataSchema.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tank.hpp"

class GamePanel
{
public:
	GamePanel(std::shared_ptr<AudioManager> audioManager, std::shared_ptr<NetworkManager> networkManager, std::shared_ptr<AssetManager> assetManager, const std::string& username);
	~GamePanel();
	bool run();
private:
	sf::RenderWindow window{ sf::VideoMode(800,600), "Game" };
	std::shared_ptr<AudioManager> m_audioManager{ nullptr };
	std::shared_ptr<NetworkManager> m_networkManager{ nullptr };
	std::shared_ptr<AssetManager> m_assetManager{ nullptr };
	std::vector<Tank> m_tanks{};
	std::vector<Player> m_players{};
	std::uint64_t m_playerId{};
	std::string m_username{};
	bool m_isRunning{ true };
};