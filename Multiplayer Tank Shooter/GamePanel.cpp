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
	m_isRunning = false;
	if (m_networkThread.joinable()) {
		m_networkThread.join();
	}
}

bool GamePanel::run()
{
	auto idAndPlayerContainer = m_networkManager->playerJoinHandle(m_username);
	m_playerId = idAndPlayerContainer.first;
	m_players = idAndPlayerContainer.second;
	m_assetManager->LoadTexture("TankTexture_1", "Assets/Images/PNG/Hulls_Color_A/Hull_01.png");

	for (const Player& player : m_players)
	{
		m_tanks.emplace_back(player, TANK_TYPE_1, m_assetManager->GetTexture("TankTexture_1"));
	}

	m_networkThread = std::thread(&GamePanel::networkLoop, this);

	while (window.isOpen())
		{
		//m_networkManager->receiveUpdates(m_players);
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						m_tanks[m_playerId].moveTo(Direction::EAST, m_networkManager);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						m_tanks[m_playerId].moveTo(Direction::NORTH, m_networkManager);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						m_tanks[m_playerId].moveTo(Direction::WEST, m_networkManager);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						m_tanks[m_playerId].moveTo(Direction::SOUTH, m_networkManager);
					}
					break;

				default:
					break;
				}
					
				
			}
			
			
			window.clear(sf::Color::White);
			render();
			window.display();
		}
	

		return 0;
	
	return false;
}

void GamePanel::networkLoop()
{
	while (m_isRunning) {
		m_networkManager->receiveUpdates(m_players);
	}
}

bool GamePanel::render()
{
	for (Tank& tank : m_tanks)
	{
		tank.draw(window);
	}
	return true;
}
