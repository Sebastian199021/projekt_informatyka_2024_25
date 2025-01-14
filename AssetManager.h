#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
// Klasa zarz�dza zasobami gry (tekstury, czcionki)
class AssetManager {
private:
    // Mapy przechowuj�ce nazwy zasobu
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;

public:
    // Funkcja �aduje tekstury i zapisuje je w mapie textures
    bool loadTexture(const std::string& name, const std::string& filePath);

    // Referencja do za�adowanej tekstury
    const sf::Texture& getTexture(const std::string& name) const;

    // To samo co z teksturami, ale dla czcionek
    bool loadFont(const std::string& name, const std::string& filePath);

    const sf::Font& getFont(const std::string& name) const;

    // Tworzenie obiektu sf::Text na podstawie za�adowanej czcionki
    sf::Text createText(const std::string& fontName, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) const;
};

#endif