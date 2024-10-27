#pragma once
#include <SFML/Graphics.hpp>

class AnimatedSprite {
public:
    AnimatedSprite(const sf::Texture& texture, int frameCount, float speed)
        : m_texture(texture), m_frameCount(frameCount), m_speed(speed) {
        m_sprite.setTexture(m_texture);
        m_sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x / frameCount, texture.getSize().y));
        m_currentFrame = 0;
        m_timePerFrame = 1.f / m_speed;
        m_timer = 0.f;
    }

    void update(float deltaTime) {
        m_timer += deltaTime;
        if (m_timer >= m_timePerFrame) {
            m_timer = 0.f;
            m_currentFrame = (m_currentFrame + 1) % m_frameCount;
            m_sprite.setTextureRect(sf::IntRect(m_currentFrame * (m_texture.getSize().x / m_frameCount), 0,
                m_texture.getSize().x / m_frameCount, m_texture.getSize().y));
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }

private:
    sf::Sprite m_sprite;
    const sf::Texture& m_texture;
    int m_frameCount;
    float m_speed;
    float m_timePerFrame;
    float m_timer;
    int m_currentFrame;
};