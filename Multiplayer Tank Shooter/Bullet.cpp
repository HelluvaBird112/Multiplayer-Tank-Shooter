#include "Bullet.hpp"

#include <cmath>
#include <iostream>


constexpr double M_PI = 3.14159;


static void angleToCartesian(double angle, double& x, double& y) {
	std::cout << "angle: " << angle << "\n";
	

	y = cos(angle);
	x = sin(angle);
}

Bullet::Bullet(BulletData& bulletData, std::shared_ptr<sf::Texture> texture)
	: m_data {bulletData},
	m_texture {texture}
{
	m_sprite.setTexture(*texture);
	
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	
}

void Bullet::update(double deltaTime)
{

	m_data.currentPos.x += deltaTime * m_data.direction.x * 100;
	m_data.currentPos.y += deltaTime * m_data.direction.y * 100;

}

void Bullet::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition({ static_cast<float>(m_data.currentPos.x) + 25,static_cast<float>(m_data.currentPos.y) + 30});
	//std::cout << "rotation: " << atan2(m_data.direction.y, m_data.direction.x) << "\n";
	m_sprite.setRotation(atan2(m_data.direction.y, m_data.direction.x) * 180 / 3.14 + 90);
	m_sprite.setScale({ 0.5,0.5 });
	window.draw(m_sprite);


}



bool Bullet::isOutside()
{
	return false;
}
