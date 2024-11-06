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
	window.setFramerateLimit(60);
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
	auto playerJoinPack = m_networkManager->playerJoinHandle(m_username);
	std::cout << "Current player id: " << playerJoinPack.player_id << "\n";
	m_playerId = playerJoinPack.player_id;
	m_players = playerJoinPack.players;
	
	m_assetManager->LoadTexture("TankTexture_1", "Assets/Images/PNG/Hulls_Color_A/Hull_01.png");
	m_assetManager->LoadTexture("TankWeaponTexture_1", "Assets/Images/PNG/Weapon_Color_A/Gun_01.png");
	m_assetManager->LoadTexture("Bullet_1", "Assets/Images/PNG/Effects/Medium_Shell.png");
	auto texture = m_assetManager->GetTexture("TankTexture_1");
	auto weaponTexture = m_assetManager->GetTexture("TankWeaponTexture_1");
	auto bulletTexture = m_assetManager->GetTexture("Bullet_1");
	
	for (const Player& player : m_players)
	{
			m_tanks.emplace_back(player, TANK_TYPE_1, texture, weaponTexture);
			std::cout << "playerid: " << m_tanks[player.id].m_player.id << "\n";
			std::cout << "playerId::::: " << player.id << "\n";
	}

	for (BulletData& bulletData : playerJoinPack.bullets)
	{
		m_bullets.emplace_back(bulletData, bulletTexture);
	}

	

	m_networkThread = std::thread(&GamePanel::networkLoop, this);

	auto lastTime = high_resolution_clock::now();
	while (window.isOpen())
		{
		//m_networkManager->receiveUpdates(m_players);
		auto currentTime = high_resolution_clock::now();
		auto deltaTime = duration_cast<duration<double>>(currentTime - lastTime).count();
		lastTime = currentTime;

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						auto& this_player = m_tanks[m_playerId].m_player;

						DirectionVector direction{ sf::Mouse::getPosition(window).x - this_player.pos.x, sf::Mouse::getPosition(window).y - this_player.pos.y };

						direction = direction.normalize();
						m_networkManager->player_shot_handle(m_playerId, direction);
					}
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						m_tanks[m_playerId].moveTo(Direction::EAST, m_networkManager);
						//m_tanks[m_playerId].m_sprite.setRotation(90);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						m_tanks[m_playerId].moveTo(Direction::NORTH, m_networkManager);
						//m_tanks[m_playerId].m_sprite.setRotation(0);

					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						m_tanks[m_playerId].moveTo(Direction::WEST, m_networkManager);
						//m_tanks[m_playerId].m_sprite.setRotation(270);

					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						m_tanks[m_playerId].moveTo(Direction::SOUTH, m_networkManager);
						//m_tanks[m_playerId].m_sprite.setRotation(180);

					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						auto& this_player = m_tanks[m_playerId].m_player;

						DirectionVector direction{ sf::Mouse::getPosition(window).x - this_player.pos.x, sf::Mouse::getPosition(window).y - this_player.pos.y };

						direction = direction.normalize();
						m_networkManager->player_shot_handle(m_playerId, direction);
					}
					break;
				
				case sf::Event::MouseMoved:
				{
					auto& this_player = m_tanks[m_playerId].m_player;
					auto mouse_pos = sf::Mouse::getPosition(window);
							
					auto dy = this_player.pos.y - mouse_pos.y;
					auto dx = this_player.pos.x - mouse_pos.x;

					auto weapon_tangent = atan2(dy, dx) * 180 / 3.14 - 90;					
					m_networkManager->player_rotate_weapon_handle(weapon_tangent, m_playerId);

					
					break;
				}
				

				default:
					break;
				}
					
				
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(50));
			
			window.clear(sf::Color::White);
			render(deltaTime);
			window.display();
		
		}
	

		return 0;
	
	return false;
}

void GamePanel::networkLoop()
{
	std::lock_guard<std::mutex> lock{ mt };
	while (m_isRunning) {
		m_networkManager->receiveUpdates(m_tanks, m_bullets);
	}
}

bool GamePanel::render(double deltaTime)
{
	//std::lock_guard<std::mutex> lock{ mt };
	for (Tank& tank : m_tanks)
	{
		if (tank.m_player.isActive)
		{
			tank.draw(window);
		}
	}

	for (Bullet& bullet : m_bullets)
	{
		if(bullet.m_data.isActive)
		{ 
			bullet.update(deltaTime);
			bullet.draw(window);
		}
		
	}
	return true;
}
