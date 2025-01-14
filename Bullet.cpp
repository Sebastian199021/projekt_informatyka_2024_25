#include "Bullet.h"

// Konstruktor klasy bullet inicjalizuje pocisk
Bullet::Bullet(float x, float y, float width, float height, float speed, sf::Color color)
    : speed(speed) {
    shape.setSize({ width, height });
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

// Ruch pocisku
void Bullet::move() {
    shape.move(0, speed);
}

// Sprawdza czy pocisk jest poza ekranem
bool Bullet::isOutOfBounds(float windowHeight) const {
    return (speed > 0 && shape.getPosition().y > windowHeight) ||
        (speed < 0 && shape.getPosition().y + shape.getSize().y < 0);
}

// Rysowanie pocisku
void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

// Zwraca granice pocisku potrzebne do kolizji
sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}