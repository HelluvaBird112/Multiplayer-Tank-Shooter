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
	auto a = m_networkManager->sendRequest<std::string , std::pair<size_t, std::vector<Player>> > (PLAYER_JOIN, m_username);
	auto numPlayer = a.first;
	m_players = a.second;
	std::cout << "NumPLayer: " << numPlayer << "\n";
	
	return false;
}
