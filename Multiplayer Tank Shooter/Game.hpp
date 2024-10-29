#pragma once
#include "AudioManager.hpp"
#include "NetworkManager.hpp"
#include "AssetManager.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
class Game
{
public:
	Game();
	~Game();
	bool run();
private:
	tgui::Gui m_gui{};
	sf::Sound m_sound{};
	tgui::Picture::Ptr m_bg{nullptr};
	tgui::Button::Ptr m_joinGameBtn{ nullptr };
	tgui::EditBox::Ptr m_editBox{ nullptr };
	sf::RenderWindow m_window;
	std::shared_ptr<AudioManager> m_audioManager{nullptr};
	std::shared_ptr<NetworkManager> m_networkManager{nullptr};
	std::shared_ptr<AssetManager> m_assetManager{nullptr};
};