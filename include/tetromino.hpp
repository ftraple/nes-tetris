#ifndef TETRIS_INCLUDE_TETROMINO_HPP_
#define TETRIS_INCLUDE_TETROMINO_HPP_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "block.hpp"

namespace tetris {

BlockType randowSelect();

class Tetromino {
   public:
    Tetromino(std::shared_ptr<sf::RenderWindow> window,
              BlockType type, int x, int y, int grid_pixel_amount);

    void reset(BlockType type);

    int x() const;

    int y() const;

    BlockType type() const;

    BlockType matrix(int position) const;

    int matrixDimension() const;

    void moveBottom();

    void moveUp();

    void moveLeft();

    void moveRight();

    void rotateClockwise();

    void rotateAntiClockwise();

    void draw();

   private:
    std::shared_ptr<sf::RenderWindow> m_window;
    BlockType m_type;
    int m_initial_x;
    int m_initial_y;
    int m_x;
    int m_y;
    int m_grid_pixel_amount;
    int m_matrix_dimension;
    std::vector<BlockType> m_matrix;
    sf::RectangleShape m_rect;

    void AllocateMatrix();
};

};  // namespace tetris

#endif  // TETRIS_INCLUDE_TETROMINO_HPP_
