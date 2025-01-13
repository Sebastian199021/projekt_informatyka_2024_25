#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Alien.h"
#include "AssetManager.h"
#include "Bullet.h"
#include "Spaceship.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>

// Funkcja pomocnicza do zapisu wyniku do pliku:
void saveScoreToFile(const std::string& name, int score) {
    std::ofstream file("scores.txt", std::ios::app); // Otwieramy plik w trybie dopisywania
    if (file.is_open()) {
        file << name << " " << score << std::endl; // Zapisujemy nick i wynik
    }
    file.close();
}

//funkcja inicializuj�ca gr�, textury, teksty - zasoby
bool initializeGame(AssetManager& assetManager, sf::RenderWindow& window, sf::Text& scoreText, sf::Text& livesText, sf::Text& gameOverText, sf::Text& finalScoreText, sf::Text& pauseText, int windowWidth, int windowHeight) {
    if (!assetManager.loadTexture("spaceship", "New Piskel4.png")) return false;
    if (!assetManager.loadTexture("alien", "alien3.png")) return false;
    if (!assetManager.loadFont("default", "arial.ttf")) return false;

    scoreText = assetManager.createText("default", "Score: 0", 24, sf::Color::White, { 10, 10 });
    livesText = assetManager.createText("default", "Lives: 3", 24, sf::Color::White, { 10, 40 });
    gameOverText = assetManager.createText("default", "GAME OVER", 48, sf::Color::Red, { windowWidth / 2.0f - 120.0f, windowHeight / 2.0f - 50.0f });
    finalScoreText = assetManager.createText("default", "", 36, sf::Color::White, { windowWidth / 2.0f - 120.0f, windowHeight / 2.0f + 20.0f });
    pauseText = assetManager.createText("default", "Game Paused\nPress Escape to Resume\nPress Enter to Quit", 36, sf::Color::Yellow, { windowWidth / 2.0f - 200.0f, windowHeight / 2.0f - 50.0f });

    return true;
}

//obs�uga zdarze�
void handleEvents(
    sf::RenderWindow& window,
    sf::Event& event,
    bool& isPaused,
    bool& enterName,
    std::string& playerName,
    int& score,
    sf::Text& enterNameText,
    const AssetManager& assetManager,
    bool& gameOver
) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            isPaused = !isPaused;
        }

        if (isPaused && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            window.close();
        }

        if (gameOver && !enterName) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (!playerName.empty()) {
                        playerName.pop_back();
                    }
                }
                else if (event.text.unicode == '\r') { // Enter
                    enterName = true;
                    saveScoreToFile(playerName, score);
                }
                else if (playerName.size() < 15 && isprint(event.text.unicode)) { // Printable character
                    playerName += static_cast<char>(event.text.unicode);
                }
                enterNameText.setString("Enter your name: " + playerName + "_");
            }
        }
    }
}

void renderGame(
    sf::RenderWindow& window,
    const Spaceship& spaceship,
    const std::vector<Bullet>& playerBullets,
    const std::vector<Bullet>& alienBullets,
    const std::vector<Alien>& aliens,
    const sf::Text& scoreText,
    const sf::Text& livesText)
{
    window.clear(sf::Color::Black);

    spaceship.draw(window);
    for (const auto& bullet : playerBullets) bullet.draw(window);
    for (const auto& bullet : alienBullets) bullet.draw(window);
    for (const auto& alien : aliens) alien.draw(window);

    window.draw(scoreText);
    window.draw(livesText);

    window.display();
}

enum MenuOption { Play, Scores, Exit };

MenuOption showMainMenu(sf::RenderWindow& window, const AssetManager& assetManager) {
    // Utworzenie opcji menu
    sf::Text playOption = assetManager.createText("default", "1. Play", 36, sf::Color::White, { 300, 200 });
    sf::Text scoresOption = assetManager.createText("default", "2. Scores", 36, sf::Color::White, { 300, 260 });
    sf::Text exitOption = assetManager.createText("default", "3. Quit", 36, sf::Color::White, { 300, 320 });

    std::vector<sf::Text*> menuOptions = { &playOption, &scoresOption, &exitOption };
    int selectedOption = 0;
    menuOptions[selectedOption]->setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return Exit;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menuOptions[selectedOption]->setFillColor(sf::Color::White);
                    selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
                    menuOptions[selectedOption]->setFillColor(sf::Color::Yellow);
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    menuOptions[selectedOption]->setFillColor(sf::Color::White);
                    selectedOption = (selectedOption + 1) % menuOptions.size();
                    menuOptions[selectedOption]->setFillColor(sf::Color::Yellow);
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    return static_cast<MenuOption>(selectedOption);
                }
            }
        }

        window.clear(sf::Color::Black);
        for (const auto& option : menuOptions) {
            window.draw(*option);
        }
        window.display();
    }

    return Exit;
}


// Funkcja wy�wietlaj�ca wyniki
void displayScores(sf::RenderWindow& window, const AssetManager& assetManager) {
    std::ifstream file("scores.txt");
    if (!file.is_open()) {
        std::cerr << "Nie mo�na otworzy� pliku scores.txt!" << std::endl;
        return;
    }

    std::vector<std::pair<std::string, int>> scores;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (iss >> name >> score) {
            scores.emplace_back(name, score);
        }
    }
    file.close();

    // Sortowanie wynik�w od najwi�kszego do najmniejszego
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // Wy�wietlanie maksymalnie 15 wynik�w
    const int maxScores = 15;
    sf::Text title = assetManager.createText("default", "Top Scores", 48, sf::Color::White, { 250, 50 });
    std::vector<sf::Text> scoreTexts;
    for (size_t i = 0; i < std::min(scores.size(), static_cast<size_t>(maxScores)); ++i) {
        const auto& [name, score] = scores[i];
        std::string entry = std::to_string(i + 1) + ". " + name + " - " + std::to_string(score);
        sf::Text text = assetManager.createText("default", entry, 24, sf::Color::White, { 200, 120 + static_cast<float>(i) * 30 });
        scoreTexts.push_back(text);
    }

    // P�tla renderuj�ca wyniki
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Zamkni�cie aplikacji
                return;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                MenuOption selectedOption = showMainMenu(window, assetManager);
                return; // Wyj�cie z wy�wietlania wynik�w, powr�t do menu
            }

        }

        window.clear(sf::Color::Black);
        window.draw(title);
        for (const auto& text : scoreTexts) {
            window.draw(text);
        }
        window.display();
    }
}

void handlePauseEvents(
    sf::RenderWindow& window,
    sf::Event& event,
    bool& isPaused,
    bool& goToMenu
) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (isPaused && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isPaused = false; // Wznowienie gry
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                goToMenu = true; // Powr�t do menu
                isPaused = false;
            }
        }
    }
}


int main()
{

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int windowWidth = 750;
    const int windowHeight = 500;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Space Invaders");
    window.setFramerateLimit(80);



    AssetManager assetManager;
    sf::Text scoreText, livesText, gameOverText, finalScoreText, pauseText;

    if (!initializeGame(assetManager, window, scoreText, livesText, gameOverText, finalScoreText, pauseText, windowWidth, windowHeight)) {
        return -1;
    }

    MenuOption selectedOption = showMainMenu(window, assetManager);
    if (selectedOption == Exit) {
        return 0;
    }
    else if (selectedOption == Scores) {
        displayScores(window, assetManager);

        // Powtarzaj menu, dop�ki nie wybierzemy innej opcji
        while (true) {
            selectedOption = showMainMenu(window, assetManager);

            if (selectedOption == Scores) {
                displayScores(window, assetManager); // Ponowne wy�wietlenie wynik�w
                continue;
            }
            else if (selectedOption == Play) {
                break; // Wyj�cie z p�tli, rozpocz�cie gry
            }
            else if (selectedOption == Exit) {
                return 0; // Zamkni�cie programu
            }
        }
    }

    int score = 0;

    Spaceship spaceship(assetManager.getTexture("spaceship"), windowWidth / 2.0f - 40.0f, windowHeight - 100.0f, 5.0f, 5.0f);


    std::vector<Bullet> playerBullets, alienBullets;
    const float bulletSpeed = 8.0f;
    const float alienBulletSpeed = 4.0f;
    const float bulletWidth = 5.0f;
    const float bulletHeight = 10.0f;
    sf::Clock shootClock, alienShootClock;
    const float shootDelay = 0.5f;
    float alienShootDelay = 1.5f;

    std::vector<Alien> aliens;
    const int alienRows = 4;
    const int alienCols = 12;
    const float alienScale = 1.3f;
    const float alienSpacing = 10.0f;
    float alienSpeed = 0.7;
    sf::Clock alienMoveClock;
    const float alienMoveDelay = 0.02f;

    float alienDirection = 1.0f;
    bool moveDown = false;
    bool gameOver = false;
    bool isPaused = false;
    bool goToMenu = false;

    std::string playerName; // Przechowuje nick gracza
    bool enterName = false; // Flaga, czy gracz wprowadza nick
    sf::Text enterNameText; // Tekst wy�wietlany podczas wprowadzania nicku

    //enterNameText.setFont(font);
    enterNameText.setFont(assetManager.getFont("default"));
    enterNameText.setCharacterSize(24);
    enterNameText.setFillColor(sf::Color::White);
    enterNameText.setPosition(windowWidth / 2.0f - 150.0f, windowHeight / 2.0f + 50.0f); // Pozycja pod napisem "GAME OVER"

    bool nextLevel = false;                  // Flaga do obs�ugi przej�cia na nowy poziom
    int currentLevel = 1;                    // Numer aktualnego poziomu
    const float alienShootDelayReduction = 0.3f; // Zmniejszenie czasu mi�dzy strza�ami kosmit�w na poziom
    const float alienSpeedIncrease = 0.3f;       // Zwi�kszenie pr�dko�ci kosmit�w na poziom

    // Dodaj tekst wy�wietlaj�cy numer poziomu
    sf::Text levelText;
    levelText.setFont(assetManager.getFont("default"));

    levelText.setCharacterSize(36);
    levelText.setFillColor(sf::Color::White);
    levelText.setString("Level " + std::to_string(currentLevel));
    levelText.setPosition(windowWidth / 2.0f - 100.0f, windowHeight / 2.0f - 50.0f);


    for (int row = 0; row < alienRows; ++row) {
        for (int col = 0; col < alienCols; ++col) {
            float x = col * (40 + alienSpacing) + 50;
            float y = row * (30 + alienSpacing) + 50;
            aliens.emplace_back(assetManager.getTexture("alien"), x, y, alienScale);
        }
    }


    while (window.isOpen()) {
        sf::Event event;


        if (isPaused) {
            handlePauseEvents(window, event, isPaused, goToMenu);

            if (goToMenu) {
                // Wywo�anie menu g��wnego
                MenuOption selectedOption = showMainMenu(window, assetManager);
                if (selectedOption == Play) {
                    // Restart gry (opcjonalne resetowanie stanu gry)
                    score = 0;
                    spaceship = Spaceship(assetManager.getTexture("spaceship"), windowWidth / 2.0f - 40.0f, windowHeight - 100.0f, 5.0f, 5.0f);
                    playerBullets.clear();
                    alienBullets.clear();
                    aliens.clear();
                    for (int row = 0; row < alienRows; ++row) {
                        for (int col = 0; col < alienCols; ++col) {
                            float x = col * (40 + alienSpacing) + 50;
                            float y = row * (30 + alienSpacing) + 50;
                            aliens.emplace_back(assetManager.getTexture("alien"), x, y, alienScale);
                        }
                    }
                }
                else if (selectedOption == Scores) {
                    // Wy�wietlanie wynik�w
                    displayScores(window, assetManager);
                    continue; // Powr�t do menu po wy�wietleniu wynik�w
                }
                else if (selectedOption == Exit) {
                    window.close();
                    return 0; // Zamkni�cie gry
                }

                goToMenu = false; // Reset flagi po powrocie z menu
                continue;
            }

            // Wy�wietl ekran pauzy
            window.clear(sf::Color::Black);
            window.draw(pauseText);
            window.display();
            continue;
        }

        handleEvents(window, event, isPaused, enterName, playerName, score, enterNameText, assetManager, gameOver);

        if (nextLevel) {
            window.clear(sf::Color::Black);
            window.draw(levelText); // Wy�wietl numer poziomu
            window.display();
            sf::sleep(sf::seconds(2)); // Pauza przed rozpocz�ciem nowego poziomu
            nextLevel = false;

            // Zwi�kszenie trudno�ci
            alienShootDelay = std::max(0.5f, alienShootDelay - alienShootDelayReduction); // Minimalna warto�� to 0.5 sekundy
            alienSpeed += alienSpeedIncrease;

            // Resetowanie kosmit�w
            aliens.clear();
            for (int row = 0; row < alienRows; ++row) {
                for (int col = 0; col < alienCols; ++col) {
                    float x = col * (40 + alienSpacing) + 50;
                    float y = row * (30 + alienSpacing) + 50;
                    aliens.emplace_back(assetManager.getTexture("alien"), x, y, alienScale);

                }
            }

            // Aktualizacja napisu z numerem poziomu
            levelText.setString("Level " + std::to_string(currentLevel));
        }



        if (!gameOver) {

            // Obs�uga sterowania statkiem
            spaceship.handleInput();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (shootClock.getElapsedTime().asSeconds() > shootDelay) {
                    playerBullets.push_back(spaceship.shoot(bulletWidth, bulletHeight, bulletSpeed, sf::Color::Red));
                    shootClock.restart();
                }
            }

            // Ruch pocisk�w
            for (auto& bullet : playerBullets) bullet.move();
            playerBullets.erase(std::remove_if(playerBullets.begin(), playerBullets.end(),
                [&windowHeight](const Bullet& b) { return b.isOutOfBounds(windowHeight); }), playerBullets.end());

            for (auto& bullet : alienBullets) bullet.move();
            alienBullets.erase(std::remove_if(alienBullets.begin(), alienBullets.end(),
                [&windowHeight](const Bullet& b) { return b.isOutOfBounds(windowHeight); }), alienBullets.end());

            // Strzelanie kosmit�w
            if (alienShootClock.getElapsedTime().asSeconds() > alienShootDelay && !aliens.empty()) {
                int randomAlienIndex = std::rand() % aliens.size();
                auto alienPosition = aliens[randomAlienIndex].getPosition();
                alienBullets.emplace_back(alienPosition.x + 16, alienPosition.y + 32, bulletWidth, bulletHeight, alienBulletSpeed, sf::Color::Green);
                alienShootClock.restart();
            }

            // Kolizje pocisk�w gracza z kosmitami
            for (auto& alien : aliens) {
                for (auto it = playerBullets.begin(); it != playerBullets.end();) {
                    if (alien.checkCollision(it->getBounds())) {
                        alien.markHit();
                        it = playerBullets.erase(it);
                        score += 10;
                    }
                    else {
                        ++it;
                    }
                }
            }

            // Kolizje pocisk�w kosmit�w z graczem
            for (auto it = alienBullets.begin(); it != alienBullets.end();) {
                if (spaceship.getBounds().intersects(it->getBounds())) {
                    spaceship.takeDamage();
                    it = alienBullets.erase(it);
                }
                else {
                    ++it;
                }
            }

            aliens.erase(std::remove_if(aliens.begin(), aliens.end(), [](const Alien& a) {
                return a.shouldBeRemoved();
                }), aliens.end());

            if (aliens.empty() && spaceship.getLives() > 0 && !gameOver) {
                currentLevel++;   // Zwi�ksz numer poziomu
                nextLevel = true; // Ustaw flag� przej�cia na nowy poziom
            }

            // Ruch kosmit�w
            if (alienMoveClock.getElapsedTime().asSeconds() > alienMoveDelay) {
                float maxX = 0.0f;
                float minX = windowWidth;

                for (const auto& alien : aliens) {
                    maxX = std::max(maxX, alien.getBounds().left + alien.getBounds().width);
                    minX = std::min(minX, alien.getBounds().left);
                }

                if ((alienDirection > 0 && maxX >= windowWidth - 10.0f) || (alienDirection < 0 && minX <= 10.0f)) {// 10.0f pozwala na zmian� kierunku przed wyj�ciem za ekran(zapas)
                    alienDirection = -alienDirection;
                    moveDown = true;
                }

                for (auto& alien : aliens) {
                    alien.move(alienDirection * alienSpeed, moveDown ? 10.0f : 0.0f);
                }

                moveDown = false;
                alienMoveClock.restart();
            }

            scoreText.setString("Score: " + std::to_string(score));
            livesText.setString("Lives: " + std::to_string(spaceship.getLives()));

            // Rysowanie gry
            renderGame(window, spaceship, playerBullets, alienBullets, aliens, scoreText, livesText);


            if (spaceship.getLives() <= 0) {
                gameOver = true;
                finalScoreText.setString("Final Score: " + std::to_string(score));
            }
        }

        if (gameOver) {
            if (!enterName) { // Je�eli gracz nie wprowadza� jeszcze nicku
                while (true) {
                    // Wy�wietlenie statycznego ekranu
                    window.clear(sf::Color::Black);

                    window.draw(gameOverText);
                    window.draw(finalScoreText);

                    enterNameText.setString("Enter your name: " + playerName + "_"); // Wy�wietlaj wprowadzany tekst
                    window.draw(enterNameText);

                    window.display();


                    // Obs�uga zdarze� wprowadzania nicku
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                            return 0;
                        }
                        if (event.type == sf::Event::TextEntered) {
                            if (event.text.unicode == '\b') { // Obs�uga klawisza Backspace
                                if (!playerName.empty()) {
                                    playerName.pop_back();
                                }
                            }
                            else if (event.text.unicode == '\r') { // Enter ko�czy wprowadzanie
                                enterName = true;
                                saveScoreToFile(playerName, score); // Zapisujemy wynik do pliku
                            }
                            else if (playerName.size() < 15 && isprint(event.text.unicode)) { // Ograniczenie d�ugo�ci nicku
                                playerName += static_cast<char>(event.text.unicode);
                            }
                        }
                    }
                    if (enterName) {
                        // Wywo�anie menu po zapisaniu nazwy gracza
                        MenuOption selectedOption = showMainMenu(window, assetManager);
                        if (selectedOption == Play) {
                            // Restart gry
                            score = 0;
                            spaceship = Spaceship(assetManager.getTexture("spaceship"), windowWidth / 2.0f - 40.0f, windowHeight - 100.0f, 5.0f, 5.0f);
                            playerBullets.clear();
                            alienBullets.clear();
                            aliens.clear();
                            for (int row = 0; row < alienRows; ++row) {
                                for (int col = 0; col < alienCols; ++col) {
                                    float x = col * (40 + alienSpacing) + 50;
                                    float y = row * (30 + alienSpacing) + 50;
                                    aliens.emplace_back(assetManager.getTexture("alien"), x, y, alienScale);
                                }
                            }
                        }
                        else if (selectedOption == Exit) {
                            window.close();
                            return 0;
                        }
                        break; // Opuszczenie p�tli obs�ugi wpisywania nazwy
                    }

                }
                window.close();
                return 0;

            }
            else { // Po wprowadzeniu nicku wy�wietl ekran ko�cowy
                window.clear(sf::Color::Black);
                window.draw(gameOverText);
                window.draw(finalScoreText);
                window.display();
            }
        }
    }
    return 0;
}