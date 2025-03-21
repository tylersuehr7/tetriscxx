#include "block.hpp"
#include <algorithm>

using namespace tetris;

static constexpr const struct {
    const Grid::ColorId id;
    const Block::cell_t data[Block::s_num_rotations][Block::s_num_cells];
} s_blocks[Block::BLOCK_MAX] = {
    {
        .id=Grid::COLOR_ID_GREEN,
        .data={
            {{0,0},{1,0},{2,0},{2,1}},
            {{0,0},{0,1},{0,2},{1,0}},
            {{0,0},{0,1},{1,1},{2,1}},
            {{1,0},{1,1},{1,2},{0,2}},
        }
    }, // LBlock
    {
        .id=Grid::COLOR_ID_BLUE,
        .data={
            {{0,1},{1,1},{2,1},{2,0}},
            {{0,0},{1,0},{1,1},{1,2}},
            {{0,1},{1,1},{2,1},{0,2}},
            {{0,0},{0,1},{0,2},{1,2}},
        }
    }, // JBlock
    {
        .id=Grid::COLOR_ID_ORANGE,
        .data={
            {{0,0},{1,0},{2,0},{3,0}},
            {{0,0},{0,1},{0,2},{0,3}},
            {{0,0},{1,0},{2,0},{3,0}},
            {{0,0},{0,1},{0,2},{0,3}},
        }
    }, // IBlock
    {
        .id=Grid::COLOR_ID_LIGHTBLUE,
        .data={
            {{1,0},{0,1},{1,1},{1,2}},
            {{0,1},{1,1},{2,1},{1,2}},
            {{1,0},{1,1},{2,1},{1,2}},
            {{1,0},{0,1},{1,1},{2,1}},
        }
    }, // TBlock
    {
        .id=Grid::COLOR_ID_YELLOW,
        .data={
            {{0,0},{1,0},{0,1},{1,1}},
            {{0,0},{1,0},{0,1},{1,1}},
            {{0,0},{1,0},{0,1},{1,1}},
            {{0,0},{1,0},{0,1},{1,1}},
        }
    }, // OBlock
    {
        .id=Grid::COLOR_ID_PURPLE,
        .data={
            {{1,0},{0,1},{1,1},{0,2}},
            {{0,0},{1,0},{1,1},{2,1}},
            {{1,0},{0,1},{1,1},{0,2}},
            {{0,0},{1,0},{1,1},{2,1}},
        }
    }, // SBlock
    {
        .id=Grid::COLOR_ID_RED,
        .data={
            {{0,0},{0,1},{1,1},{1,2}},
            {{1,0},{2,0},{0,1},{1,1}},
            {{0,0},{0,1},{1,1},{1,2}},
            {{1,0},{2,0},{0,1},{1,1}},
        }
    }, // ZBlock
};

void Block::draw() const {
    const auto& proxy = s_blocks[m_type];
    for (const auto& cell : proxy.data[m_rotation]) {
        DrawRectangle(
            (cell.col + m_col_offset) * Grid::s_cell_size + Grid::s_padding,  // COLUMN
            (cell.row + m_row_offset) * Grid::s_cell_size + Grid::s_padding,  // ROW
            Grid::s_cell_size - Grid::s_cell_margin,
            Grid::s_cell_size - Grid::s_cell_margin,
            Grid::s_cell_colors[proxy.id]
        );
    }
}

void Block::draw_preview(const Rectangle &bounds) const {
    const auto& proxy = s_blocks[m_type];
    
    // Find the block's boundaries
    int min_row = 0, max_row = 0, min_col = 0, max_col = 0;
    for (const auto& cell : proxy.data[m_rotation]) {
        min_row = std::min(min_row, cell.row);
        max_row = std::max(max_row, cell.row);
        min_col = std::min(min_col, cell.col);
        max_col = std::max(max_col, cell.col);
    }
    
    // Calculate block dimensions
    const float block_width = (max_col - min_col + 1) * Grid::s_cell_size;
    const float block_height = (max_row - min_row + 1) * Grid::s_cell_size;
    
    // Calculate scaling to fit in bounds while maintaining aspect ratio
    const float scale = std::min(bounds.width / block_width, bounds.height / block_height) * s_preview_scale;
    
    // Calculate centered position
    const float cell_size = Grid::s_cell_size * scale;
    const float start_x = bounds.x + (bounds.width - block_width * scale) / 2;
    const float start_y = bounds.y + (bounds.height - block_height * scale) / 2;
    
    // Draw the block
    for (const auto& cell : proxy.data[m_rotation]) {
        DrawRectangle(
            start_x + cell.col * cell_size,
            start_y + cell.row * cell_size,
            cell_size - Grid::s_cell_margin * scale,
            cell_size - Grid::s_cell_margin * scale,
            Grid::s_cell_colors[proxy.id]
        );
    }
}

Block& Block::clone(const Block &block) {
    m_type = block.m_type;
    m_rotation = block.m_rotation;
    m_row_offset = block.m_row_offset;
    m_col_offset = block.m_col_offset;
    return *this;
}

Block& Block::move_by(const int &rows, const int &cols) {
    m_row_offset += rows;
    m_col_offset += cols;
    return *this;
}

Block& Block::rotate() {
    m_rotation = (m_rotation + 1) % 4;
    return *this;
}

Block& Block::undo_rotate() {
    m_rotation = (m_rotation - 1 + 4) % 4;
    return *this;
}

Block& Block::randomize() {
    const BlockType new_type = (BlockType) GetRandomValue(0, BLOCK_MAX - 1);
    m_type = new_type;
    m_row_offset = 0;
    m_col_offset = (Grid::s_num_cols - 1) >> 1;
    m_rotation = 0;
    return *this;
}

const int& Block::get_row_offset() const {
    return m_row_offset;
}

const int& Block::get_col_offset() const {
    return m_col_offset;
}

const Block::cell_t& Block::get_cell(const int &position) const {
    return s_blocks[m_type].data[m_rotation][position];
}

const Block::BlockType& Block::get_block_type() const {
    return m_type;
}

const Grid::ColorId& Block::get_color_id() const {
    return s_blocks[m_type].id;
}
