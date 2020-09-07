#ifndef TESTRIS_INCLUDE_GAME_LOGIC_HPP_
#define TESTRIS_INCLUDE_GAME_LOGIC_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "collision.hpp"
#include "game-over.hpp"
#include "play-field.hpp"
#include "score.hpp"
#include "tetromino.hpp"

namespace tetris {

class GameLogic {
    public:
    GameLogic(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font, int grid_pixel_amount);

    bool isPlaying();

    void run();

    private:
    std::shared_ptr<sf::RenderWindow> m_window;
    const sf::Font& m_font;
    int m_grid_pixel_amount;
    PlayField m_play_field;
    Tetromino m_tetromino;
    Tetromino m_next_tetromino;
    Score m_score;
    int m_tetromino_elapse{0};
    int m_speed{1000};
    bool m_soft_drop_active{false};
    int m_soft_drop_start{0};
    int m_soft_drop_end{0};
    sf::Clock m_clock;
    sf::Text m_text_next;
    bool m_is_runnig{false};

    sf::SoundBuffer m_sound_move_buffer;
    sf::Sound m_sound_move;

    sf::SoundBuffer m_sound_rotate_buffer;
    sf::Sound m_sound_rotate;

    sf::SoundBuffer m_sound_drop_buffer;
    sf::Sound m_sound_drop;

    sf::SoundBuffer m_sound_clear_line_buffer;
    sf::Sound m_sound_clear_line;

    sf::Music m_music_1;

    void event();

    void update();

    void draw();

    void moveBotton();

    void updateSpeed();
};

}  // namespace tetris

#endif  // TESTRIS_INCLUDE_GAME_LOGIC_HPP_