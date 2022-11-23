#ifndef TETRIS_INCLUDE_BLOCK_TYPE_HPP_
#define TETRIS_INCLUDE_BLOCK_TYPE_HPP_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <map>
#include <vector>

namespace tetris {

enum class BlockType : uint8_t {
    empty,
    I,
    O,
    T,
    J,
    L,
    S,
    Z
};

inline std::map<BlockType, sf::Color> BlockColor{
    {BlockType::empty, sf::Color{0, 0, 0, 255}},
    {BlockType::I, sf::Color{80, 208, 255, 255}},
    {BlockType::O, sf::Color{255, 224, 32, 255}},
    {BlockType::T, sf::Color{255, 0, 255, 255}},
    {BlockType::J, sf::Color{0, 32, 255, 255}},
    {BlockType::L, sf::Color{255, 160, 16, 255}},
    {BlockType::S, sf::Color{0, 192, 0, 255}},
    {BlockType::Z, sf::Color{255, 0, 0, 255}}};

};  // namespace tetris

#endif  // TETRIS_INCLUDE_BLOCK_TYPE_HPP_
