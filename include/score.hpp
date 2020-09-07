#ifndef TETRIS_INCLUDE_SCORE_HPP_
#define TETRIS_INCLUDE_SCORE_HPP_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <sstream>
#include <memory>

namespace tetris {

class Score {
    public:
    Score(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font);

    void increasePointsForLine(int number_of_lines);

    void increaseSoftDropPoints(int number_of_cells);

    int score();

    int level();

    void draw();

    private:
    std::shared_ptr<sf::RenderWindow> m_window;
    int m_top_score{10000};
    int m_score{0};
    int m_level{0};
    int m_line_amount{0};

    sf::Text m_text_a_type;
    sf::Text m_text_top_score;
    sf::Text m_text_score;
    sf::Text m_text_level;
    sf::Text m_text_lines;

    void updateLevel();
};

}  // namespace tetris

#endif  // TETRIS_INCLUDE_SCORE_HPP_