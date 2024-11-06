#include "Tank.hpp"
#include "Enum.hpp"
#include <cmath>
#include <SFML/Window/Mouse.hpp>
Tank::Tank(const Player& player, TankType tankType, std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Texture> weapon_texture) :
	m_player {player},
	m_tanktype {tankType},
	m_texture {texture},
	m_weapon_texture {weapon_texture}
{
	m_texture->setSmooth(true);
	m_texture->setRepeated(false);
	m_sprite.setTexture(*(m_texture.get()));
	m_sprite.setScale({ 0.2,0.2 });
	m_sprite.setPosition({ static_cast<float>(player.pos.x),static_cast<float>(player.pos.y)});

	m_weapon_texture->setSmooth(true);
	m_weapon_texture->setRepeated(false);
	m_weapon_sprite.setTexture(*(m_weapon_texture.get()));
	m_weapon_sprite.setScale({ 0.2,0.2 });
	m_weapon_sprite.setOrigin(m_weapon_sprite.getLocalBounds().width / 2, m_weapon_sprite.getLocalBounds().height /5 * 4);

	m_weapon_sprite.setPosition({ static_cast<float>(player.pos.x) + 25,static_cast<float>(player.pos.y) + 30 });
}

void Tank::update()
{
}

void Tank::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition({ static_cast<float>(m_player.pos.x),static_cast<float>(m_player.pos.y) });
	m_weapon_sprite.setPosition({ static_cast<float>(m_player.pos.x) + 25,static_cast<float>(m_player.pos.y) + 30});

	window.draw(m_sprite);

	
	m_weapon_sprite.setRotation(m_player.traverseAngle);
	window.draw(m_weapon_sprite);
	//std::cout << "draw  player has id: " << m_player.id << " x:" << m_player.pos.x << " y: " << m_player.pos.y << "\n";
}



void Tank::moveTo(Direction dir, std::shared_ptr<NetworkManager> networkManager) const
{
	std::cout << "this tank has id: " << m_player.id << " MOVE to " << dir << "\n";
	networkManager->playerMoveHandle(dir, m_player.id);
	
	
}

void Tank::fire()
{
}
