#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

// Klasa reprezentuj�ca statek
class Spaceship {
public:
    //Konstruktor inicjalizuj�cy statek
    Spaceship(const sf::Texture& texture, float x, float y, float scale, float speed);
    void move(float dx); // Ruch statku
    void draw(sf::RenderWindow& window) const; //Rysowanie
    void handleInput(); // Metoda do obs�ugi ruchu statku
    //Tworzenie pocisku
    Bullet shoot(float bulletWidth, float bulletHeight, float bulletSpeed, sf::Color bulletColor) const;
    sf::FloatRect getBounds() const; // Zwraca granice statku
    void takeDamage(); // Zmniejszanie liczby �y�
    int getLives() const;  // Zwraca aktualn� liczb� �y�
    sf::Vector2f getPosition() const;  // Aktualna pozycja statku

private:
    sf::Sprite sprite; //Grafika statku
    float speed;
    int lives;
    // Rozmiary klatki na teksturze
    static constexpr int frameWidth = 16;
    static constexpr int frameHeight = 16;
};

#endif