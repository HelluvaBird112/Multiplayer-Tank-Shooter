
#pragma once
#include <SFML/Graphics.hpp>
#include "Enum.hpp"
#include "DataSchema.hpp"
class Bullet {
public:
    Bullet(BulletData& bulletData, std::shared_ptr<sf::Texture> texture);
    void update(double deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOutside();

    sf::Sprite m_sprite;
    std::shared_ptr<sf::Texture> m_texture;
    BulletData m_data;
};

