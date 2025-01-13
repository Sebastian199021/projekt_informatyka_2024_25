#include "AssetManager.h"
#include <iostream>

bool AssetManager::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Nie mo¿na za³adowaæ tekstury: " << filePath << std::endl;
        return false;
    }
    textures[name] = std::move(texture);
    return true;
}

const sf::Texture& AssetManager::getTexture(const std::string& name) const {
    return textures.at(name);
}

bool AssetManager::loadFont(const std::string& name, const std::string& filePath) {
    sf::Font font;
    if (!font.loadFromFile(filePath)) {
        std::cerr << "Nie mo¿na za³adowaæ czcionki: " << filePath << std::endl;
        return false;
    }
    fonts[name] = std::move(font);
    return true;
}

const sf::Font& AssetManager::getFont(const std::string& name) const {
    return fonts.at(name);
}

sf::Text AssetManager::createText(const std::string& fontName, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) const {
    sf::Text text;
    text.setFont(fonts.at(fontName));
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}