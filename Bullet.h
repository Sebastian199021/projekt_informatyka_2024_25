#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

// Klasa bullet reprezentuje w grze pocisk
class Bullet {
public:
    // Konstruktor inicjalizuje pocisk (po³o¿enie pocz¹tkowe, wymiary, prêdkoœæ, kolor)
    Bullet(float x, float y, float width, float height, float speed, sf::Color color);
    void move(); // Ruch
    bool isOutOfBounds(float windowHeight) const; // Sprawdza czy pocisk nie jest poza ekranem
    void draw(sf::RenderWindow& window) const; // Rysuje pocisk
    sf::FloatRect getBounds() const; // Zwraca granice pocisku

private:
    sf::RectangleShape shape; // Kszta³t pocisku
    float speed; // prêdkoœæ pocisku
};

#endif