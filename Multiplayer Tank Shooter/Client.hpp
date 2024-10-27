#pragma once
#include <string>
#include <TGUI/TGUI.hpp>
#include "Menu.hpp"
#include "Game.hpp"#include <memory>
#include <TGUI/Backend/SFML-Graphics.hpp>
class Client
{
public:
	Client();
	~Client();

	bool run();
	
private:
	std::shared_ptr<sf::RenderWindow> m_window{};
	std::shared_ptr<Menu> m_menu{};
	std::shared_ptr<Game> m_game{};
	std::shared_ptr<AudioManager> m_audioManager{};
	std::shared_ptr<NetworkManager> m_networkManager{};
	std::shared_ptr<AssetManager> m_assetManager{};
};