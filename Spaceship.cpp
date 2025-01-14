#include "Spaceship.h"
#include <SFML/Window/Keyboard.hpp>
#include "Bullet.h"

// Konstruktor klasy inicjalizuje statek
Spaceship::Spaceship(const sf::Texture& texture, float x, float y, float scale, float speed)
    : speed(speed), lives(3) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
}

// Ruch statku
void Spaceship::move(float dx) {
    sprite.move(dx * speed, 0);
}

// Rysowanie statku
void Spaceship::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

// Wejœcia - sterowanie statkiem
void Spaceship::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(-1); // Przesuwamy statek w lewo
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(1); // Przesuwamy statek w prawo
    }
}

// Kolizje statku
sf::FloatRect Spaceship::getBounds() const {
    return sprite.getGlobalBounds();
}

// Funkcja tworz¹ca pocisk
Bullet Spaceship::shoot(float bulletWidth, float bulletHeight, float bulletSpeed, sf::Color bulletColor) const {
    return Bullet(
        sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - bulletWidth / 2, // Œrodek statku na osi X
        sprite.getPosition().y - bulletHeight + 20.0f, // Górna krawêdŸ statku - wysokoœæ pocisku
        bulletWidth, bulletHeight, -bulletSpeed, bulletColor);
}

// Zmniejszanie liczby ¿yæ
void Spaceship::takeDamage() {
    if (lives > 0) {
        lives--;
    }
}

// Funkcja zwraca aktualn¹ liczbê ¿yæ
int Spaceship::getLives() const {
    return lives;
}

// Zwracanie aktualnej pozycji statku
sf::Vector2f Spaceship::getPosition() const {
    return sprite.getPosition();
}