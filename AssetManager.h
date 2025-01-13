#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:
    // Funkcja ³adowania tekstur
    bool loadTexture(const std::string& name, const std::string& filePath);

    // Pobranie tekstury
    const sf::Texture& getTexture(const std::string& name) const;

    // Funkcja ³adowania czcionek
    bool loadFont(const std::string& name, const std::string& filePath);

    // Pobranie czcionki
    const sf::Font& getFont(const std::string& name) const;

    // Tworzenie tekstu
    sf::Text createText(const std::string& fontName, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) const;
};

#endif // ASSETMANAGER_H