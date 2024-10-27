#pragma once

#include "Bullet.hpp"
#include "Enum.hpp"
#include "DataSchema.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

struct Position
{
    int32_t x;
    int32_t y;
};

class Tank {
public:
    Tank(float startX, float startY);
    void update();
    void draw(sf::RenderTarget& target);
    void move(Direction dir);
    void fire();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    std::vector<Bullet> bullets;
    PLayer m_player;
};

