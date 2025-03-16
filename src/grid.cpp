#include "grid.hpp"

using namespace tetris;

void Grid::draw() const {
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

const bool Grid::is_cell_empty(const unsigned int &row, const unsigned int &col) const {
    return m_cells[row][col] == COLOR_ID_EMPTY;
}

const bool Grid::is_off_grid(const int &adjusted_row, const int &adjusted_col) const {
    return adjusted_row < 0 || adjusted_col < 0 || adjusted_row >= s_num_rows || adjusted_col >= s_num_cols;
}

int Grid::clear_full_rows() {
    unsigned int row, num_rows_cleared = 0;
    
    for (row = s_num_rows - 1; row > 0; row--) {
        if (is_row_full(row)) {
            clear_row(row);
            num_rows_cleared++;
        } else if (num_rows_cleared > 0) {
            move_row_down(row, num_rows_cleared);
        }
    }

    return num_rows_cleared;
}

bool Grid::is_row_full(const unsigned int &row) const {
    bool row_is_full = true;
    unsigned int col;

    for (col = 0; col < s_num_cols; col++) {
        if (m_cells[row][col] == 0) {
            row_is_full = false;
            break;
        }
    }

    return row_is_full;
}

void Grid::clear_row(const unsigned int &row) {
    unsigned int col;
    for (col = 0; col < s_num_cols; col++) {
        m_cells[row][col] = Grid::COLOR_ID_EMPTY;
    }
}

void Grid::move_row_down(const unsigned int &row, const unsigned int &num_rows_cleared) {
    unsigned int col;
    for (col = 0; col < s_num_cols; col++) {
        m_cells[row + num_rows_cleared][col] = m_cells[row][col];
        m_cells[row][col] = Grid::COLOR_ID_EMPTY;
    }
}
