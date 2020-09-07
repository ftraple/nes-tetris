#include "play-field.hpp"

namespace tetris {

PlayField::PlayField(std::shared_ptr<sf::RenderWindow> window,
                     int x, int y, int width, int height, int grid_pixel_amount)
    : m_window{window},
      m_x(x),
      m_y(y),
      m_width(width),
      m_height(height),
      m_grid_pixel_amount(grid_pixel_amount),
      m_matrix(width * height, BlockType::empty) {
    m_background.setPosition(m_x * m_grid_pixel_amount, m_y * m_grid_pixel_amount);
    m_background.setSize(sf::Vector2f{float(m_width * m_grid_pixel_amount), float(m_height * m_grid_pixel_amount)});
    m_background.setFillColor(sf::Color{16, 16, 16, 255});
    m_background.setOutlineColor(sf::Color::White);
    m_background.setOutlineThickness(4);

    m_block.setSize(sf::Vector2f{float(m_grid_pixel_amount - 1), float(m_grid_pixel_amount - 1)});
    m_block.setFillColor(sf::Color::Blue);
    m_block.setOutlineColor(sf::Color::White);
    m_block.setOutlineThickness(1);
}

int PlayField::x() const {
    return m_x;
}

int PlayField::y() const {
    return m_y;
}

int PlayField::width() const {
    return m_width;
}

int PlayField::height() const {
    return m_height;
}

const std::vector<BlockType>& PlayField::matrix() const {
    return m_matrix;
}

void PlayField::draw() {
    m_window->draw(m_background);
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            BlockType value = m_matrix[y * m_width + x];
            if (value != BlockType::empty) {
                m_block.setFillColor(BlockColor[value]);
                m_block.setPosition((m_x + x) * m_grid_pixel_amount, (m_y + y) * m_grid_pixel_amount);
                m_window->draw(m_block);
            }
        }
    }
}

void PlayField::addTetromino(const Tetromino& tetromino) {
    int tetromino_x = tetromino.x() - m_x;
    int tetromino_y = tetromino.y() - m_y;
    int tetromino_matrix_dimension = tetromino.matrixDimension();

    for (int y = 0; y < tetromino_matrix_dimension; y++) {
        for (int x = 0; x < tetromino_matrix_dimension; x++) {
            if (tetromino_x + x >= 0 && tetromino_x + x < m_width &&
                tetromino_y + y >= 0 && tetromino_y + y < m_height) {
                const BlockType value = tetromino.matrix(y * tetromino_matrix_dimension + x);
                if (value != BlockType::empty) {
                    m_matrix[(tetromino_y + y) * m_width + (tetromino_x + x)] = value;
                }
            }
        }
    }
}

int PlayField::removeCompleLines(const Tetromino& tetromino) {
    int lines_removed{0};
    int tetromino_y = tetromino.y() - m_y;
    int tetromino_matrix_dimension = tetromino.matrixDimension();
    for (int y = tetromino_y; y < tetromino_y + tetromino_matrix_dimension; y++) {
        bool line_is_full{true};
        for (int x = 0; x < m_width; x++) {
            if (m_matrix[y * m_width + x] == BlockType::empty) {
                line_is_full = false;
                break;
            }
        }
        if (line_is_full) {
            removeLine(y);
            lines_removed++;
        }
    }
    return lines_removed;
}

void PlayField::removeLine(int line) {
    for (int y = line; y > 1; y--) {
        for (int x = 0; x < m_width; x++) {
            int i = y * m_width + x;
            m_matrix[i] = m_matrix[i - m_width];
        }
    }
}

}  // namespace tetris