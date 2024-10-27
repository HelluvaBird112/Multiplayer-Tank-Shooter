#pragma once

#include "Bullet.hpp"
#include "Enum.hpp"

#include <SFML/Graphics.hpp>
#include <vector>


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
};

