#include "AssetManager.h"
#include <iostream>
// �adowanie tekstury z pliku do mapy textures
bool AssetManager::loadTexture(const std::string& name, const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) { // �adowanie tekstury z pliku
        std::cerr << "Nie mo�na za�adowa� tekstury: " << filePath << std::endl;
        return false;
    }
    textures[name] = std::move(texture); // Przechowywanie tekstury w mapie z odpowiedni� nazw�
    return true;
}
// Dost�p do tekstury na podstawie nazwy
const sf::Texture& AssetManager::getTexture(const std::string& name) const {
    return textures.at(name);
}
// Tak jak z tekstur�, �adowanie czcionki
bool AssetManager::loadFont(const std::string& name, const std::string& filePath) {
    sf::Font font;
    if (!font.loadFromFile(filePath)) {
        std::cerr << "Nie mo�na za�adowa� czcionki: " << filePath << std::endl;
        return false;
    }
    fonts[name] = std::move(font);
    return true;
}
// Zwracanie referencji do czcionki przechowywanej w fonts
const sf::Font& AssetManager::getFont(const std::string& name) const {
    return fonts.at(name);
}
// Tworzenie obiektu tekstowego z wykorzystaniem za�adowanej czcionki
sf::Text AssetManager::createText(const std::string& fontName, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) const {
    sf::Text text;
    text.setFont(fonts.at(fontName));
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}