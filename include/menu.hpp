#ifndef TETRIS_INCLUDE_MENU_HPP_
#define TETRIS_INCLUDE_MENU_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "game-logic.hpp"

namespace tetris {

enum class MenuOption {
    start,
    config,
    record
};

inline MenuOption& operator++(MenuOption& option, int) {
    option = (option == MenuOption::record) ? MenuOption::start : MenuOption(static_cast<int>(option) + 1);
    return option;
}

inline MenuOption& operator--(MenuOption& option, int) {
    option = (option == MenuOption::start) ? MenuOption::record : MenuOption(static_cast<int>(option) - 1);
    return option;
}

class Menu {
    public:
    Menu(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font);

    void run();

    private:
    std::shared_ptr<sf::RenderWindow> m_window;
    const sf::Font& m_font;
    sf::Texture m_title_texture;
    sf::Sprite m_sprite;
    sf::Text m_start;
    sf::Text m_text_selector;
    sf::Text m_text_config;
    sf::Text m_text_record;
    MenuOption m_option_selected{MenuOption::start};

    void event();

    void draw();
};

}  // namespace tetris

#endif  // TETRIS_INCLUDE_MENU_HPP_