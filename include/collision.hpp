#ifndef TETRIS_INCLUDE_COLLISION_HPP_
#define TETRIS_INCLUDE_COLLISION_HPP_

#include <cstdint>
#include <vector>

#include "play-field.hpp"
#include "tetromino.hpp"

namespace tetris {

bool checkMatrixOverlap(const Tetromino& tetromino, const PlayField& play_field);

}

#endif  // TETRIS_INCLUDE_COLLISION_HPP_