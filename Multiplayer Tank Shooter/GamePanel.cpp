#include "GamePanel.hpp"

GamePanel::GamePanel(std::shared_ptr<AudioManager> audioManager, std::shared_ptr<NetworkManager> networkManager, std::shared_ptr<AssetManager> assetManager)
{

}

GamePanel::~GamePanel()
{
}

bool GamePanel::run()
{
	auto a = m_networkManager->sendRequest<bool, std::tuple<int64_t, std::vector<Player>>>(PLAYER_JOIN, std::nullopt);
}
