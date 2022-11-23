#ifndef TESTRIS_INCLUDE_PLAY_FIELD_HPP_
#define TESTRIS_INCLUDE_PLAY_FIELD_HPP_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include "block.hpp"
#include "tetromino.hpp"

namespace tetris {

class PlayField {
   public:
    PlayField(std::shared_ptr<sf::RenderWindow> window,
              int x, int y, int width, int height, int grid_pixel_amount);

    int x() const;

    int y() const;

    int width() const;

    int height() const;

    const std::vector<BlockType>& matrix() const;

    void draw();

    void addTetromino(const Tetromino& tetromino);

    int removeCompleteLines(const Tetromino& tetromino);

   private:
    std::shared_ptr<sf::RenderWindow> m_window;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_grid_pixel_amount;
    std::vector<BlockType> m_matrix;
    sf::RectangleShape m_block;
    sf::RectangleShape m_background;

    void removeLine(int line);
};

}  // namespace tetris

#endif  // TESTRIS_INCLUDE_PLAY_FIELD_HPP_
