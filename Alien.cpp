#include "Alien.h"

Alien::Alien(const sf::Texture& texture, float x, float y, float scale)
    : isHit(false), currentFrame(0) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
}

void Alien::markHit() {
    isHit = true;
    currentFrame = 1;
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
    hitClock.restart();
}

bool Alien::shouldBeRemoved() const {
    return isHit && hitClock.getElapsedTime().asSeconds() > removalDelay;
}

void Alien::draw(sf::RenderWindow& window) const {
    if (!shouldBeRemoved()) {
        window.draw(sprite);
    }
}

bool Alien::checkCollision(const sf::FloatRect& bounds) {
    return !isHit && getBounds().intersects(bounds);
}

void Alien::move(float dx, float dy) {
    sprite.move(dx, dy);
}

sf::FloatRect Alien::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float shrinkWidth = bounds.width * 0.3f;
    float shrinkHeight = bounds.height * 0.3f;
    return sf::FloatRect(bounds.left + shrinkWidth / 2, bounds.top + shrinkHeight / 2,
        bounds.width - shrinkWidth, bounds.height - shrinkHeight);
}

sf::Vector2f Alien::getPosition() const {
    return sprite.getPosition();
}