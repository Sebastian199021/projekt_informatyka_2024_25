#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    // Konstruktor
    Player();

    // Metoda aktualizuj�ca ruch na podstawie klawiszy
    void update(float deltaTime);

    // Metoda do renderowania Pac-Mana na ekranie
    void render(sf::RenderWindow& window);

private:
    sf::CircleShape shape;  // Kszta�t Pac-Mana
    float speed;            // Pr�dko�� ruchu Pac-Mana
};

#endif
