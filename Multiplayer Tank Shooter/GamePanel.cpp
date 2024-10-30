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
	m_assetManager->LoadTexture("TankTexture_1", "Assets/Images/PNG/Hulls_Color_A/Hull_01.png");

	for (const Player& player : m_players)
	{
		m_tanks.emplace_back(player, TANK_TYPE_1, m_assetManager->GetTexture("TankTexture_1"));
	}
	while (m_isRunning)
	{
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					m_tanks[m_playerId].move(Direction::NORTH);
				}
			}

			window.clear(sf::Color::Black);

			render();
			window.display();
		}

		return 0;
	}
	return false;
}

bool GamePanel::render()
{
	for (Tank tank : m_tanks)
	{
		tank.draw(window);
	}
	return true;
}
