#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "menu.hpp"

int main() {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "NES-Tetris");

    sf::Font font;
    if (!font.loadFromFile("resource/font/OpenSans-Bold.ttf")) {
        return EXIT_FAILURE;
    }

    tetris::Menu menu(window, font);
    menu.run();

    return EXIT_SUCCESS;
}
