#include "grid.hpp"

Grid::Grid(): m_cells() {
    reset_cells();
}

void Grid::draw() {
    for (auto row = 0; row < s_num_rows; row++) {
        for (auto col = 0; col < s_num_cols; col++) {
            DrawRectangle(
                col * s_cell_size + s_padding,  // Column
                row * s_cell_size + s_padding,  // Row
                s_cell_size - 1,
                s_cell_size - 1,
                s_cell_colors[m_cells[row][col]]
            );
        }
    }
}

void Grid::reset_cells() {
    for (auto & m_cell : m_cells) {
        for (auto & col : m_cell) {
            col = ColorId::COLOR_ID_EMPTY;
        }
    }
}

void Grid::set_cell_color(const unsigned int &row, const unsigned int &col, const ColorId &id) {
    m_cells[row][col] = id;
}

bool Grid::is_cell_empty(const unsigned int &row, const unsigned int &col) {
    return m_cells[row][col] == COLOR_ID_EMPTY;
}

bool Grid::is_a_cell(const int &row_offset, const int &col_offset) {
    return row_offset >= 0 && row_offset < s_num_rows && col_offset >= 0 && col_offset < s_num_cols;
}
