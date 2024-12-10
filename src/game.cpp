#include "game.hpp"

Game::Game(const Vector2 &size): m_size(size), m_grid(Grid()), m_block(Block()) {
}

void Game::on_process_input() {
    switch (GetKeyPressed()) {
    case KEY_LEFT:
        move_block_left();
        break;
    case KEY_RIGHT:
        move_block_right();
        break;
    case KEY_DOWN:
        move_block_down();
        break;
    case KEY_UP:
        rotate_block();
        break;
    }
}

void Game::on_update() {
}

void Game::on_render() {
    ClearBackground(BLACK);
    m_grid.draw();
    m_block.draw();
}

void Game::rotate_block() {
    m_block.rotate();
    if (is_block_touching_another_block_or_off_grid()) {
        m_block.undo_rotate();
    }
}

void Game::move_block_left() {
    m_block.move_by(0, -1);
    if (is_block_touching_another_block_or_off_grid()) {
        m_block.move_by(0, 1);
    }
}

void Game::move_block_right() {
    m_block.move_by(0, 1);
    if (is_block_touching_another_block_or_off_grid()) {
        m_block.move_by(0, -1);
    }
}

void Game::move_block_down() {
    m_block.move_by(1, 0);
    if (is_block_touching_another_block_or_off_grid()) {
        m_block.move_by(-1, 0);
    }
}

bool Game::is_block_touching_another_block_or_off_grid() {
    int position, trans_row, trans_col;
    for (position = 0; position < Block::s_num_cells; position++) {
        const auto& cell = m_block.get_cell(position);

        trans_row = cell.row + m_block.get_row_offset();
        trans_col = cell.col + m_block.get_col_offset();

        if (!m_grid.is_a_cell(trans_row, trans_col) || !m_grid.is_cell_empty(trans_row, trans_col)) {
            return true;
        }
    }
    return false;
}
