#include "tetromino.hpp"

namespace tetris {

BlockType randowSelect() {
    std::srand(std::time(nullptr));
    return (BlockType)((std::rand() % 7) + 1);
}

Tetromino::Tetromino(std::shared_ptr<sf::RenderWindow> window,
                     BlockType type, int x, int y, int grid_pixel_amount)
    : m_window{window},
      m_type{type},
      m_initial_x{x},
      m_initial_y{y},
      m_x{x},
      m_y{y},
      m_grid_pixel_amount{grid_pixel_amount} {
    AllocateMatrix();
    m_rect.setSize(sf::Vector2f{m_grid_pixel_amount - 1.0f, m_grid_pixel_amount - 1.0f});
    m_rect.setOutlineColor(sf::Color::White);
    m_rect.setOutlineThickness(1);
}

void Tetromino::reset(BlockType type) {
    m_type = type;
    m_x = m_initial_x;
    m_y = m_initial_y;
    m_matrix.clear();
    AllocateMatrix();
}

void Tetromino::AllocateMatrix() {
    BlockType x = BlockType::empty;
    BlockType I = BlockType::I;
    BlockType O = BlockType::O;
    BlockType T = BlockType::T;
    BlockType J = BlockType::J;
    BlockType L = BlockType::L;
    BlockType S = BlockType::S;
    BlockType Z = BlockType::Z;

    if (m_type == BlockType::I) {
        m_matrix_dimension = 4;
        m_matrix = {
            x, x, x, x,
            I, I, I, I,
            x, x, x, x,
            x, x, x, x};
    } else if (m_type == BlockType::O) {
        m_matrix_dimension = 4;
        m_matrix = {
            x, x, x, x,
            x, O, O, x,
            x, O, O, x,
            x, x, x, x};
    } else if (m_type == BlockType::T) {
        m_matrix_dimension = 3;
        m_matrix = {
            x, x, x,
            T, T, T,
            x, T, x};
    } else if (m_type == BlockType::J) {
        m_matrix_dimension = 3;
        m_matrix = {
            x, x, x,
            J, J, J,
            x, x, J};
    } else if (m_type == BlockType::L) {
        m_matrix_dimension = 3;
        m_matrix = {
            x, x, x,
            L, L, L,
            L, x, x};
    } else if (m_type == BlockType::S) {
        m_matrix_dimension = 3;
        m_matrix = {
            x, x, x,
            x, S, S,
            S, S, x};
    } else if (m_type == BlockType::Z) {
        m_matrix_dimension = 3;
        m_matrix = {
            x, x, x,
            Z, Z, x,
            x, Z, Z};
    }
}

int Tetromino::x() const {
    return m_x;
}

int Tetromino::y() const {
    return m_y;
}

BlockType Tetromino::type() const {
    return m_type;
}

BlockType Tetromino::matrix(int position) const {
    return m_matrix[position];
}

int Tetromino::matrixDimension() const {
    return m_matrix_dimension;
}

void Tetromino::moveBotton() {
    m_y++;
}

void Tetromino::moveUp() {
    m_y--;
}

void Tetromino::moveLeft() {
    m_x--;
}

void Tetromino::moveRight() {
    m_x++;
}

void Tetromino::rotateClockwize() {
    std::vector<BlockType> matrix_tmp(m_matrix.begin(), m_matrix.end());
    int i = 0;
    for (int x = 0; x < m_matrix_dimension; x++) {
        for (int y = m_matrix_dimension - 1; y >= 0; y--) {
            m_matrix[i++] = matrix_tmp[y * m_matrix_dimension + x];
        }
    }
}

void Tetromino::rotateAntiClockwize() {
    std::vector<BlockType> matrix_tmp(m_matrix.begin(), m_matrix.end());
    int i = 0;
    for (int x = m_matrix_dimension - 1; x >= 0; x--) {
        for (int y = 0; y < m_matrix_dimension; y++) {
            m_matrix[i++] = matrix_tmp[y * m_matrix_dimension + x];
        }
    }
}

void Tetromino::draw() {
    for (int y = 0; y < m_matrix_dimension; y++) {
        for (int x = 0; x < m_matrix_dimension; x++) {
            BlockType block_type = m_matrix[y * m_matrix_dimension + x];
            if (block_type != BlockType::empty) {
                m_rect.setFillColor(BlockColor[block_type]);
                m_rect.setPosition((m_x + x) * m_grid_pixel_amount, (m_y + y) * m_grid_pixel_amount);
            }
            m_window->draw(m_rect);
        }
    }
}

}  // namespace tetris