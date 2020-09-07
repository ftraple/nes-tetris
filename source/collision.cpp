#include "collision.hpp"

namespace tetris {

bool checkMatrixOverlap(const Tetromino& tetromino, const PlayField& play_field) {
    int tetromino_x = tetromino.x() - play_field.x();
    int tetromino_y = tetromino.y() - play_field.y();
    int tetromino_matrix_dimension = tetromino.matrixDimension();

    auto play_field_matrix = play_field.matrix();
    int play_field_width = play_field.width();
    int play_field_height = play_field.height();

    for (int y = 0; y < tetromino_matrix_dimension; y++) {
        for (int x = 0; x < tetromino_matrix_dimension; x++) {
            BlockType value = tetromino.matrix(y * tetromino_matrix_dimension + x);
            if (value != BlockType::empty) {
                if (tetromino_x + x < 0 || tetromino_x + x >= play_field_width ||
                    tetromino_y + y < 0 || tetromino_y + y >= play_field_height ||
                    play_field_matrix[(tetromino_y + y) * play_field_width + (tetromino_x + x)] != BlockType::empty) {
                    return true;
                }
            }
        }
    }
    return false;
}

}  // namespace tetris
