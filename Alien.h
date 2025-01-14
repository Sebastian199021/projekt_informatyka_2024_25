#ifndef ALIEN_H
#define ALIEN_H

#include <SFML/Graphics.hpp>

// Klasa alien reprezentuje przeciwnika
class Alien {
public:
    //konstruktor inicjalizuj¹cy przeciwnika
    Alien(const sf::Texture& texture, float x, float y, float scale);

    void markHit();
    bool shouldBeRemoved() const;
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const sf::FloatRect& bounds);
    void move(float dx, float dy);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    bool isHit;
    int currentFrame;
    sf::Clock hitClock;

    static constexpr int frameWidth = 32;
    static constexpr int frameHeight = 32;
    static constexpr float removalDelay = 0.5f;
};

#endif // ALIEN_H