#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    // Konstruktor
    Player();

    // Metoda aktualizuj¹ca ruch na podstawie klawiszy
    void update(float deltaTime);

    // Metoda do renderowania Pac-Mana na ekranie
    void render(sf::RenderWindow& window);

private:
    sf::CircleShape shape;  // Kszta³t Pac-Mana
    float speed;            // Prêdkoœæ ruchu Pac-Mana
};

#endif
