#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Spaceship {
public:
    Spaceship(const sf::Texture& texture, float x, float y, float scale, float speed);
    void move(float dx);
    void draw(sf::RenderWindow& window) const;
    void handleInput(); // Metoda do obs³ugi ruchu statku
    Bullet shoot(float bulletWidth, float bulletHeight, float bulletSpeed, sf::Color bulletColor) const;
    sf::FloatRect getBounds() const;
    void takeDamage();
    int getLives() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    float speed;
    int lives;
    static constexpr int frameWidth = 16; // Rozmiar statku na teksturze
    static constexpr int frameHeight = 16;
};

#endif