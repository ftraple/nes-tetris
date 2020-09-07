#include "menu.hpp"

namespace tetris {

Menu::Menu(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font)
    : m_window{window}, m_font{font} {
    if (!m_title_texture.loadFromFile("resource/image/tetris.png")) {
        std::cout << "Fail to load the title image.\n";
        exit(-1);
    }

    m_sprite.setTexture(m_title_texture);
    m_sprite.setPosition(m_window->getSize().x / 2.0f - m_title_texture.getSize().x / 2.0f, 100);

    m_start.setFont(font);
    m_start.setString("START");
    m_start.setCharacterSize(38);
    m_start.setFillColor(sf::Color::White);
    m_start.setOrigin(m_start.getLocalBounds().width / 2.0f, 0.0f);
    m_start.setPosition(m_window->getSize().x / 2.0f, 350);

    m_text_config.setFont(font);
    m_text_config.setString("CONFIG");
    m_text_config.setCharacterSize(38);
    m_text_config.setFillColor(sf::Color(32, 32, 32, 255));
    m_text_config.setOrigin(m_text_config.getLocalBounds().width / 2.0f, 0.0f);
    m_text_config.setPosition(m_window->getSize().x / 2.0f, 450);

    m_text_record.setFont(font);
    m_text_record.setString("RECORDS");
    m_text_record.setCharacterSize(38);
    m_text_record.setFillColor(sf::Color(32, 32, 32, 255));
    m_text_record.setOrigin(m_text_record.getLocalBounds().width / 2.0f, 0.0f);
    m_text_record.setPosition(m_window->getSize().x / 2.0f, 550);

    m_text_selector.setFont(font);
    m_text_selector.setString(">");
    m_text_selector.setCharacterSize(38);
    m_text_selector.setFillColor(sf::Color::Yellow);
}

void Menu::run() {
    while (m_window->isOpen()) {
        draw();
        event();
    }
}

void Menu::event() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
            break;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                m_option_selected--;
            } else if (event.key.code == sf::Keyboard::Down) {
                m_option_selected++;
            } else if (event.key.code == sf::Keyboard::Enter) {
                if (m_option_selected == MenuOption::start) {
                    GameLogic game(m_window, m_font, 32);
                    game.run();
                }
            }
        }
    }
}

void Menu::draw() {
    m_window->clear();
    m_text_selector.setPosition(350, 350 + static_cast<int>(m_option_selected) * 100);
    m_window->draw(m_sprite);
    m_window->draw(m_start);
    m_window->draw(m_text_config);
    m_window->draw(m_text_record);
    m_window->draw(m_text_selector);
    m_window->display();
}

}  // namespace tetris