#include "AssetManager.hpp"
#include <stdexcept>

// Load a texture and cache it
void AssetManager::LoadTexture(const std::string& name, const std::string& filePath) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load texture: " + filePath);
    }
    m_textures[name] = std::move(texture);
}

// Get a texture
sf::Texture& AssetManager::GetTexture(const std::string& name) {
    auto found = m_textures.find(name);
    if (found == m_textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return *(found->second);
}

// Load a font and cache it
void AssetManager::LoadFont(const std::string& name, const std::string& filePath) {
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load font: " + filePath);
    }
    m_fonts[name] = std::move(font);
}

// Get a font
sf::Font& AssetManager::GetFont(const std::string& name) {
    auto found = m_fonts.find(name);
    if (found == m_fonts.end()) {
        throw std::runtime_error("Font not found: " + name);
    }
    return *(found->second);
}

// Load a sound buffer and cache it
void AssetManager::LoadSound(const std::string& name, const std::string& filePath) {
    auto soundBuffer = std::make_unique<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load sound: " + filePath);
    }
    m_sounds[name] = std::move(soundBuffer);
}

// Get a sound buffer
sf::SoundBuffer& AssetManager::GetSound(const std::string& name) {
    auto found = m_sounds.find(name);
    if (found == m_sounds.end()) {
        throw std::runtime_error("Sound not found: " + name);
    }
    return *(found->second);
}