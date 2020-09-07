#include "game-logic.hpp"

namespace tetris {

GameLogic::GameLogic(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font, int grid_pixel_amount)
    : m_window{window},
      m_font{font},
      m_grid_pixel_amount(grid_pixel_amount),
      m_play_field(window, 11, 3, 10, 20, m_grid_pixel_amount),
      m_tetromino(window, randowSelect(), 14, 2, m_grid_pixel_amount),
      m_next_tetromino(window, randowSelect(), 23, 14, m_grid_pixel_amount),
      m_score(window, font) {
    m_text_next.setFont(font);
    m_text_next.setString("NEXT");
    m_text_next.setCharacterSize(38);
    m_text_next.setFillColor(sf::Color::White);
    m_text_next.setPosition(736, 350);

    if (!m_sound_move_buffer.loadFromFile("resource/sound/move.ogg")) {
        std::cout << "Fail to load sound: resource/sound/move.ogg\n";
    }
    m_sound_move.setBuffer(m_sound_move_buffer);
    m_sound_move.setVolume(50.0f);

    if (!m_sound_rotate_buffer.loadFromFile("resource/sound/rotate.ogg")) {
        std::cout << "Fail to load sound: resource/sound/move.ogg\n";
    }
    m_sound_rotate.setBuffer(m_sound_rotate_buffer);
    m_sound_rotate.setVolume(50.0f);

    if (!m_sound_drop_buffer.loadFromFile("resource/sound/drop.ogg")) {
        std::cout << "Fail to load sound: resource/sound/drop.ogg\n";
    }
    m_sound_drop.setBuffer(m_sound_drop_buffer);
    m_sound_drop.setVolume(50.0f);

    if (!m_sound_clear_line_buffer.loadFromFile("resource/sound/clear-line.ogg")) {
        std::cout << "Fail to load sound: resource/sound/clear-line.ogg\n";
    }
    m_sound_clear_line.setBuffer(m_sound_clear_line_buffer);
    m_sound_clear_line.setVolume(50.0f);

    if (!m_music_1.openFromFile("resource/music/music-1.ogg")) {
        std::cout << "Fail to load sound: resource/music/music-1.ogg\n";
    }
    m_music_1.setLoop(true);
    m_music_1.setVolume(20.0f);
    m_music_1.play();
}

void GameLogic::run() {
    m_is_runnig = true;
    while (m_window->isOpen() && m_is_runnig) {
        draw();
        update();
        event();
    }
}

void GameLogic::event() {
    sf::Event event;
    while (m_window->pollEvent(event) && m_is_runnig) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
            break;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                m_tetromino.moveLeft();
                if (checkMatrixOverlap(m_tetromino, m_play_field)) {
                    m_tetromino.moveRight();
                } else {
                    m_sound_move.play();
                }
            } else if (event.key.code == sf::Keyboard::Right) {
                m_tetromino.moveRight();
                if (checkMatrixOverlap(m_tetromino, m_play_field)) {
                    m_tetromino.moveLeft();
                } else {
                    m_sound_move.play();
                }
            } else if (event.key.code == sf::Keyboard::Z) {
                m_tetromino.rotateAntiClockwize();
                if (checkMatrixOverlap(m_tetromino, m_play_field)) {
                    m_tetromino.rotateClockwize();
                } else {
                    m_sound_rotate.play();
                }
            } else if (event.key.code == sf::Keyboard::X) {
                m_tetromino.rotateClockwize();
                if (checkMatrixOverlap(m_tetromino, m_play_field)) {
                    m_tetromino.rotateAntiClockwize();
                } else {
                    m_sound_rotate.play();
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                moveBotton();
                if (!m_soft_drop_active) {
                    m_soft_drop_active = true;
                    m_soft_drop_start = m_tetromino.y();
                    m_soft_drop_end = m_soft_drop_start;
                }
            }
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Down) {
                m_soft_drop_end = m_tetromino.y();
                m_soft_drop_active = false;
            }
        }
    }
}

void GameLogic::moveBotton() {
    m_tetromino.moveBotton();
    if (checkMatrixOverlap(m_tetromino, m_play_field)) {
        m_tetromino.moveUp();
        // Check if the game is over.
        if (m_tetromino.y() - m_play_field.y() <= 0) {
            m_music_1.stop();
            GameOver game_over(m_window, m_font);
            game_over.run(m_score.score(), m_score.level());
            m_is_runnig = false;
            return;
        }
        m_sound_drop.play();
        m_play_field.addTetromino(m_tetromino);
        int total_lines_removed = m_play_field.removeCompleLines(m_tetromino);
        if (total_lines_removed > 0) {
            m_sound_clear_line.play();
            m_score.increasePointsForLine(total_lines_removed);
        }
        if (m_soft_drop_active) {
            m_soft_drop_end = m_tetromino.y();
            m_soft_drop_active = false;
        }
        m_score.increaseSoftDropPoints(m_soft_drop_end - m_soft_drop_start);
        m_tetromino.reset(m_next_tetromino.type());
        m_next_tetromino.reset(randowSelect());
        updateSpeed();
    }
}

void GameLogic::updateSpeed() {
    m_speed = 1000 - (m_score.level() * 20);
    if (m_speed < 200) {
        m_speed = 200;
    }
}

void GameLogic::update() {
    uint32_t elapse = m_clock.getElapsedTime().asMilliseconds();
    if (elapse > m_tetromino_elapse + m_speed) {
        m_tetromino_elapse = elapse;
        moveBotton();
    }
}

void GameLogic::draw() {
    m_window->clear();
    m_window->draw(m_text_next);
    m_play_field.draw();
    m_tetromino.draw();
    m_next_tetromino.draw();
    m_score.draw();
    m_window->display();
}

}  // namespace tetris