#include <SFML/Graphics.hpp>
#include "Player.h"

// Sta�e do ustawienia okna gry
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "Pac-Man";

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(60);

    Player player; // Tworzymy obiekt Pac-Mana

    sf::Clock clock; // Zegar do �ledzenia deltaTime

    // P�tla g��wna gry
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); // Czas mi�dzy klatkami

        // Obs�uga zdarze�
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Aktualizacja pozycji Pac-Mana
        player.update(deltaTime);

        // Czyszczenie okna
        window.clear(sf::Color::Black);

        // Renderowanie Pac-Mana
        player.render(window);

        // Wy�wietlanie okna na ekranie
        window.display();
    }

    return 0;
}
