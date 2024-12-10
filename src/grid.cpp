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

bool Grid::is_row_full(const unsigned int &row) {
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
