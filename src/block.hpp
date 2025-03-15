#ifndef TETRIS_BLOCK_HPP
#define TETRIS_BLOCK_HPP

#include <raylib.h>
#include "grid.hpp"

namespace tetris {

class Block {
public:
    typedef struct {
        const int row;
        const int col;
    } cell_t;

    typedef enum : unsigned char {
        BLOCK_L = 0,
        BLOCK_J,
        BLOCK_I,
        BLOCK_T,
        BLOCK_O,
        BLOCK_S,
        BLOCK_Z,
        BLOCK_MAX
    } BlockType;

    typedef unsigned char BlockRotation;
public:
    static constexpr const int s_num_cells       = 4;
    static constexpr const int s_num_rotations   = 4;
    static constexpr const float s_preview_scale = 0.6f;
private:
    BlockType m_type{BLOCK_L};
    BlockRotation m_rotation{0};
    int m_row_offset{0};
    int m_col_offset{0};
public:
    Block() = default;

    // Drawing methods
    void draw() const;
    void draw_preview(const Rectangle &bounds) const;

    // State modification methods
    Block& clone(const Block &block);
    Block& move_by(const int &rows, const int &cols);
    Block& rotate();
    Block& undo_rotate();
    Block& randomize();

    // Getters
    [[nodiscard]] const int& get_row_offset() const;
    [[nodiscard]] const int& get_col_offset() const;
    [[nodiscard]] const cell_t& get_cell(const int &position) const;
    [[nodiscard]] const BlockType& get_block_type() const;
    [[nodiscard]] const Grid::ColorId& get_color_id() const;
};

}

#endif//TETRIS_BLOCK_HPP