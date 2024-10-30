#pragma once

#include "Bullet.hpp"
#include "Enum.hpp"
#include "DataSchema.hpp"
#include <SFML/Graphics.hpp>
#include "NetworkManager.hpp"
#include <vector>



class Tank {
public:
    Tank(const Player& player, TankType tankType, const sf::Texture& texture);
    void update();
    void draw(sf::RenderTarget& target);
    void move(Direction dir, std::shared_ptr<NetworkManager> networkManager);
    void fire();

private:
    sf::Sprite m_sprite{};
    sf::Texture m_texture{};
    TankType m_tanktype{};
    float m_speed{};
    std::vector<Bullet> m_bullets{};
    Player m_player{};
};

