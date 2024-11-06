#include "AssetManager.hpp"
#include <stdexcept>

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::LoadTexture(const std::string& name, const std::string& filePath) 
{
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath)) 
    {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    m_textures[name] = std::move(texture);
}

std::shared_ptr<sf::Texture> AssetManager::GetTexture(const std::string& name) 
{
    auto found = m_textures.find(name);
    if (found == m_textures.end()) 
    {
        throw std::runtime_error("Texture not found: " + name);
    }
    return found->second;
}

void AssetManager::LoadFont(const std::string& name, const std::string& filePath) 
{
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filePath)) 
    {
        throw std::runtime_error("Failed to load font: " + filePath);
    }
    m_fonts[name] = std::move(font);
}

std::shared_ptr<sf::Font> AssetManager::GetFont(const std::string& name) 
{
    auto found = m_fonts.find(name);
    if (found == m_fonts.end()) 
    {
        throw std::runtime_error("Font not found: " + name);
    }
    return found->second;
}

void AssetManager::LoadSound(const std::string& name, const std::string& filePath) 
{
    auto soundBuffer = std::make_unique<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filePath)) 
    {
        throw std::runtime_error("Failed to load sound: " + filePath);
    }
    m_sounds[name] = std::move(soundBuffer);
}

std::shared_ptr<sf::SoundBuffer> AssetManager::GetSound(const std::string& name) 
{
    auto found = m_sounds.find(name);
    if (found == m_sounds.end()) 
    {
        throw std::runtime_error("Sound not found: " + name);
    }
    return found->second;
}