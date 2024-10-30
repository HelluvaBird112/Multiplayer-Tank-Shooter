#include "Tank.hpp"
#include "Enum.hpp"

Tank::Tank(const Player& player, TankType tankType, const sf::Texture& texture) :
	m_player {player},
	m_tanktype {tankType},
	m_texture {texture}
{
	m_texture.setSmooth(true);
	m_texture.setRepeated(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale({ 0.2,0.2 });
	m_sprite.setPosition({ player.pos.x,player.pos.y });
}

void Tank::update()
{
}

void Tank::draw(sf::RenderTarget& target)
{
	m_sprite.setPosition({ m_player.pos.x,m_player.pos.y });
	target.draw(m_sprite);
}



void Tank::move(Direction dir, std::shared_ptr<NetworkManager> networkManager)
{
	auto err = networkManager->sendRequest<Direction, bool>(PLAYER_MOVE, dir);
}

void Tank::fire()
{
}
