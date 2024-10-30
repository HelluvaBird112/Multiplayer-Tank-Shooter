#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

class AssetManager {
public:
    AssetManager();
    ~AssetManager();
    void LoadTexture(const std::string& name, const std::string& filePath);
    sf::Texture& GetTexture(const std::string& name);

   
    //sf::Texture& GetAnimatedTexture(const std::string& name);

    void LoadFont(const std::string& name, const std::string& filePath);
    // Get a font
    sf::Font& GetFont(const std::string& name);

    void LoadSound(const std::string& name, const std::string& filePath);
    sf::SoundBuffer& GetSound(const std::string& name);

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures{};
    std::map<std::string, std::unique_ptr<sf::Font>> m_fonts{};
    std::map<std::string, std::unique_ptr<sf::SoundBuffer>> m_sounds{};
    //std::map<std::string, std::unique_ptr<sf::Texture>> m_animatedTexture{};
};

