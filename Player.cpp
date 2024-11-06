#include "Player.h"

// Konstruktor
Player::Player() : speed(150.0f) // Ustawienie pr�dko�ci na 150 pikseli na sekund�
{
    // Ustawienie kszta�tu jako okr�g (Pac-Man)
    shape.setRadius(20.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(100.0f, 100.0f); // Pocz�tkowa pozycja Pac-Mana
    shape.setOrigin(shape.getRadius(), shape.getRadius()); // Ustawienie �rodka jako punktu odniesienia
}

// Aktualizacja pozycji na podstawie klawiszy strza�ek
void Player::update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    // Sprawdzenie wci�ni�tych klawiszy i odpowiedni ruch
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed * deltaTime;

    // Aktualizacja pozycji Pac-Mana
    shape.move(movement);
}

// Renderowanie Pac-Mana na ekranie
void Player::render(sf::RenderWindow& window)
{
    window.draw(shape);
}
