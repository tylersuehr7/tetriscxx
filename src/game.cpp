#include "game.hpp"

Game::Game(const Vector2 &size): 
    m_size(size),
    m_started(false),
    m_game_speed(0.4f),
    m_last_update_in_secs(0.0),
    m_score(0), 
    m_grid(Grid()), 
    m_block(Block()) {
}

void Game::on_process_input() {
    if (!m_started) {
        if (KEY_ENTER == GetKeyPressed()) {
            m_started = true;
        }
        return;
    }

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
    if (!m_started) {
        return;
    }
    
    const double current_time_in_secs = GetTime();

    if (current_time_in_secs - m_last_update_in_secs < m_game_speed) {
        return;
    }

    m_last_update_in_secs = current_time_in_secs;

    move_block_down();
}

static struct {
    float width;
    Vector2 bounds;
} s_text_buffer;

void Game::on_render() {
    ClearBackground(BLACK);

    if (!m_started) {
        s_text_buffer.width = MeasureText("Welcome!", 20);
        s_text_buffer.bounds.x = (m_size.x / 2.0f) - (s_text_buffer.width / 2.0f);
        s_text_buffer.bounds.y = (m_size.y / 2.0f) - 10.0f - 20.0f - 30.0f;
        DrawText("Welcome!", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 20, WHITE);

        s_text_buffer.width = MeasureText("Tetris Clone", 30);
        s_text_buffer.bounds.x = (m_size.x / 2.0f) - (s_text_buffer.width / 2.0f);
        s_text_buffer.bounds.y += 30.0f;
        DrawText("Tetris Clone", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 30, WHITE);

        s_text_buffer.width = MeasureText("Press 'enter' to play", 12);
        s_text_buffer.bounds.x = (m_size.x / 2.0f) - (s_text_buffer.width / 2.0f);
        s_text_buffer.bounds.y += 60.0f;
        DrawText("Press 'enter' to play", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 12, WHITE);

        s_text_buffer.width = MeasureText("Powered by Suehr Gaming LLC", 10);
        s_text_buffer.bounds.x = (m_size.x / 2.0f) - (s_text_buffer.width / 2.0f);
        s_text_buffer.bounds.y = m_size.y - 30.0f;
        DrawText("Powered by Suehr Gaming LLC", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 10, WHITE);

        return;
    }

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

    update_score(0, 1);
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

void Game::update_score(const int &rows_cleared, const int &down_points) {
    switch (rows_cleared) {
    case 1:
        m_score += 100;
        break;
    case 2:
        m_score += 300;
        break;
    case 3:
        m_score += 500;
        break;
    case 4:
        m_score += 1000;
        // TODO: play tetris sound
        break;
    }
    m_score += down_points;
}
