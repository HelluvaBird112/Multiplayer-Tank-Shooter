#include "GamePanel.hpp"

GamePanel::GamePanel(std::shared_ptr<AudioManager> audioManager, std::shared_ptr<NetworkManager> networkManager, std::shared_ptr<AssetManager> assetManager) 
	: m_audioManager {audioManager},
	  m_networkManager {networkManager},
	m_assetManager {assetManager}
{

}

GamePanel::~GamePanel()
{
}

bool GamePanel::run()
{
	auto a = m_networkManager->sendRequest<bool,std::pair<size_t, std::vector<Player>>>(PLAYER_JOIN, std::nullopt);
	auto numPlayer = a.first;
	m_players = a.second;
	std::cout << "NumPLayer: " << numPlayer << "\n";
	for (const Player& player : m_players)
	{
		std::cout << "Player: " << "Ip: "<<  player.ip << " Port: " << player.port << " isActive: " << player.isActive << "\n";
	}
	return false;
}
