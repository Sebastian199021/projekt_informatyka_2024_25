#include "Alien.h"

// Konstruktor inicjalizuje obiekt przeciwnika
Alien::Alien(const sf::Texture& texture, float x, float y, float scale)
    : isHit(false), currentFrame(0) { // Inicjalizacja stanu i klatki animacji
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
}

// Funkcja oznacza obcego jako trafionego i zmienia klatkê
void Alien::markHit() {
    isHit = true; // Flaga trafienia
    currentFrame = 1;
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    hitClock.restart();
}

// Po minionym czasie ta funkcja usuwa kosmitê z ekranu
bool Alien::shouldBeRemoved() const {
    return isHit && hitClock.getElapsedTime().asSeconds() > removalDelay;
}

// Rysowanie kosmity
void Alien::draw(sf::RenderWindow& window) const {
    if (!shouldBeRemoved()) {
        window.draw(sprite);
    }
}

// Kolizje kosmitów z oknem gry
bool Alien::checkCollision(const sf::FloatRect& bounds) {
    return !isHit && getBounds().intersects(bounds);
}

// Ruch kosmity
void Alien::move(float dx, float dy) {
    sprite.move(dx, dy);
}

// Ta dunkcja zwraca granicê obcego, potrzebne do kolizji
sf::FloatRect Alien::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    // Pomniejszenie rozmiaru kolizji
    float shrinkWidth = bounds.width * 0.3f;
    float shrinkHeight = bounds.height * 0.3f;
    return sf::FloatRect(bounds.left + shrinkWidth / 2, bounds.top + shrinkHeight / 2,
        bounds.width - shrinkWidth, bounds.height - shrinkHeight);
}

// Zwraca aktualn¹ pozycjê kosmity na ekranie
sf::Vector2f Alien::getPosition() const {
    return sprite.getPosition();
}