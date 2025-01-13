#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, float width, float height, float speed, sf::Color color);
    void move();
    bool isOutOfBounds(float windowHeight) const;
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
    float speed;
};

#endif