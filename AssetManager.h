#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
// Klasa zarządza zasobami gry (tekstury, czcionki)
class AssetManager {
private:
    // Mapy przechowujące nazwy zasobu
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:
    // Funkcja ładuje tekstury i zapisuje je w mapie textures
    bool loadTexture(const std::string& name, const std::string& filePath);

    // Referencja do załadowanej tekstury
    const sf::Texture& getTexture(const std::string& name) const;

    // To samo co z teksturami, ale dla czcionek
    bool loadFont(const std::string& name, const std::string& filePath);

    const sf::Font& getFont(const std::string& name) const;

    // Tworzenie obiektu sf::Text na podstawie załadowanej czcionki
    sf::Text createText(const std::string& fontName, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) const;
};

#endif