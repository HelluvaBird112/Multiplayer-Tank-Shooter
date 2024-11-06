#pragma once
#include "NetworkManager.hpp"
#include "Bullet.hpp"
#include "Enum.hpp"
#include "DataSchema.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

class NetworkManager;

class Tank {
public:
    Tank(const Player& player, TankType tankType, std::shared_ptr<sf::Texture> tank_texture, std::shared_ptr<sf::Texture> weapon_texture);
    void update();
    void draw(sf::RenderWindow& window);
    void moveTo(Direction dir, std::shared_ptr<NetworkManager> networkManager) const;
    void fire();
    Player m_player{};


    sf::Sprite m_sprite{};
    std::shared_ptr<sf::Texture> m_texture{};
    std::shared_ptr<sf::Texture> m_weapon_texture{};
    sf::Sprite m_weapon_sprite{};
    TankType m_tanktype{};
    float m_speed{};
};

