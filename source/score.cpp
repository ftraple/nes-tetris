#include "score.hpp"

namespace tetris {

Score::Score(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font)
    : m_window{window} {
    std::stringstream str;

    m_text_a_type.setFont(font);
    m_text_a_type.setString("A-TYPE");
    m_text_a_type.setCharacterSize(38);
    m_text_a_type.setFillColor(sf::Color::White);
    m_text_a_type.setPosition(130, 30);

    m_text_lines.setFont(font);
    m_text_lines.setString("LINES - 0");
    m_text_lines.setCharacterSize(38);
    m_text_lines.setFillColor(sf::Color::White);
    m_text_lines.setPosition(430, 30);

    str << "TOP\n"
        << m_top_score << '\n';
    m_text_top_score.setFont(font);
    m_text_top_score.setString(str.str());
    m_text_top_score.setCharacterSize(38);
    m_text_top_score.setFillColor(sf::Color::White);
    m_text_top_score.setPosition(730, 30);

    m_text_score.setFont(font);
    m_text_score.setString("SCORE\n0");
    m_text_score.setCharacterSize(38);
    m_text_score.setFillColor(sf::Color::White);
    m_text_score.setPosition(730, 200);

    m_text_level.setFont(font);
    m_text_level.setString("LEVEL\n0");
    m_text_level.setCharacterSize(38);
    m_text_level.setFillColor(sf::Color::White);
    m_text_level.setPosition(730, 600);
}

void Score::increasePointsForLine(int number_of_lines) {
    m_line_amount += number_of_lines;
    std::stringstream lines_str;
    lines_str << "LINES-" << m_line_amount << '\n';
    m_text_lines.setString(lines_str.str());

    int points_for_line[5] = {0, 40, 100, 300, 1200};
    m_score += points_for_line[number_of_lines] * (m_level + 1);
    std::stringstream score_str;
    score_str << "SCORE\n"
              << m_score << '\n';
    m_text_score.setString(score_str.str());
    updateLevel();
}

void Score::increaseSoftDropPoints(int number_of_cells) {
    if (number_of_cells == 0) {
        return;
    }
    m_score += number_of_cells;
    std::stringstream score_str;
    score_str << "SCORE\n"
              << m_score << '\n';
    m_text_score.setString(score_str.str());
    updateLevel();
}

void Score::updateLevel() {
    int level = m_line_amount / 10;
    if (level != m_level) {
        m_level = level;
        std::stringstream level_str;
        level_str << "LEVEL\n"
                  << m_level << '\n';
        m_text_level.setString(level_str.str());
    }
}

int Score::score() {
    return m_score;
}

int Score::level() {
    return m_level;
}

void Score::draw() {
    m_window->draw(m_text_a_type);
    m_window->draw(m_text_top_score);
    m_window->draw(m_text_score);
    m_window->draw(m_text_level);
    m_window->draw(m_text_lines);
}

}  // namespace tetris
