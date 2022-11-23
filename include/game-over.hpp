#ifndef TETRIS_INCLUDE_GAME_OVER_HPP_
#define TETRIS_INCLUDE_GAME_OVER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>

namespace tetris {

class GameOver {
   public:
    GameOver(std::shared_ptr<sf::RenderWindow> window, const sf::Font& font);

    void run(int score, int level);

   private:
    std::shared_ptr<sf::RenderWindow> m_window;
    bool m_is_running{false};
    sf::Text m_text_type_a;
    sf::Text m_text_game_over;
    sf::Text m_text_record;
    sf::Text m_text_message;

    void event();

    void draw();
};

}  // namespace tetris

#endif  // TETRIS_INCLUDE_GAME_OVER_HPP_
