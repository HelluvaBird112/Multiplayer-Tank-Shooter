#include "GamePanel.hpp"

GamePanel::GamePanel(
	std::shared_ptr<AudioManager> audioManager,
	std::shared_ptr<NetworkManager> networkManager,
	std::shared_ptr<AssetManager> assetManager,
	const std::string& username) 
	: m_audioManager {audioManager},
	  m_networkManager {networkManager},
	  m_assetManager {assetManager},
	  m_username {username}
{

}

GamePanel::~GamePanel()
{
}

bool GamePanel::run()
{
	auto idAndPlayerContainer = m_networkManager->sendRequest<std::string , std::pair<size_t, std::vector<Player>> > (PLAYER_JOIN, m_username);
	m_playerId = idAndPlayerContainer.first;
	m_players = idAndPlayerContainer.second;
	for (const Player& player : m_players)
	{
		m_tanks.emplace_back(player.pos.x, player.pos.y );
	}
	while (m_isRunning)
	{
		
	}
	return false;
}

bool GamePanel::render()
{
	for (Tank tank : m_tanks)
	{
		tank.draw(window);
	}
	return false;
}
