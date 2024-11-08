#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    // Konstruktor
    Player();

    // Metoda aktualizująca ruch na podstawie klawiszy
    void update(float deltaTime);

    // Metoda do renderowania Pac-Mana na ekranie
    void render(sf::RenderWindow& window);

private:
    sf::CircleShape shape;  // Kształt Pac-Mana
    float speed;            // Prędkość ruchu Pac-Mana
};

#endif
