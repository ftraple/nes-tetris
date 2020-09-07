#include "game-over.hpp"

namespace tetris {

GameOver::GameOver(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font)
    : m_window{window} {
    m_text_type_a.setFont(font);
    m_text_type_a.setString("A-TYPE");
    m_text_type_a.setCharacterSize(36);
    m_text_type_a.setFillColor(sf::Color::White);
    m_text_type_a.setOrigin(m_text_type_a.getLocalBounds().width / 2.0f, 0.0f);
    m_text_type_a.setPosition(m_window->getSize().x / 2.0f, 80);

    m_text_game_over.setFont(font);
    m_text_game_over.setString("GAME OVER");
    m_text_game_over.setCharacterSize(80);
    m_text_game_over.setFillColor(sf::Color::Red);
    m_text_game_over.setOrigin(m_text_game_over.getLocalBounds().width / 2.0f, 0.0f);
    m_text_game_over.setPosition(m_window->getSize().x / 2.0f, 200);

    m_text_record.setFont(font);
    m_text_record.setCharacterSize(60);
    m_text_record.setFillColor(sf::Color::White);

    m_text_message.setFont(font);
    m_text_message.setString("PRESS ENTER TO CONTINUE");
    m_text_message.setCharacterSize(30);
    m_text_message.setFillColor(sf::Color::White);
    m_text_message.setOrigin(m_text_message.getLocalBounds().width / 2.0f, 0.0f);
    m_text_message.setPosition(m_window->getSize().x / 2.0f, 600);
}

void GameOver::run(int score, int level) {
    m_is_runnig = true;
    std::stringstream str;
    str << "SCORE: " << score << "   LEVEL: " << level;
    m_text_record.setString(str.str());
    m_text_record.setOrigin(m_text_record.getLocalBounds().width / 2.0f, 0.0f);
    m_text_record.setPosition(m_window->getSize().x / 2.0f, 400);

    while (m_window->isOpen() && m_is_runnig) {
        draw();
        event();
    }
}

void GameOver::event() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
            break;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                m_is_runnig = false;
            }
        }
    }
}

void GameOver::draw() {
    m_window->clear();
    m_window->draw(m_text_type_a);
    m_window->draw(m_text_game_over);
    m_window->draw(m_text_record);
    m_window->draw(m_text_message);
    m_window->display();
}

};  // namespace tetris
