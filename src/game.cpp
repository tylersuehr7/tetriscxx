#include "game.hpp"
#include <array>

using namespace tetris;

Game::Game(const Sounds &sounds): 
    m_sounds(sounds),
    m_block(Block().randomize()),
    m_next_block(Block().randomize()) {
}

void Game::on_update() {
    on_process_input();

    if (!m_started || m_game_over) {
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
    
    const Vector2 bounds = { .x=(float) GetScreenWidth(), .y=(float) GetScreenHeight() };

    if (!m_started) {
        draw_not_started_hud(bounds);
        return;
    }

    m_grid.draw();

    if (m_game_over) {
        draw_game_over_hud(bounds);
        return;
    }

    m_block.draw();

    draw_score_time_and_preview_hud(bounds);
}

void Game::on_process_input() {
    auto pressed_key = GetKeyPressed();

    if (pressed_key == KEY_ENTER) {
        if (!m_started) {
            m_started = true;
            return;
        } else if (m_game_over) {
            reset_game();
            return;
        }
    }

    switch (pressed_key) {
    case KEY_LEFT:
        move_block_left();
        break;
    case KEY_RIGHT:
        move_block_right();
        break;
    case KEY_DOWN:
        move_block_down();
        update_score(0, 1);
        break;
    case KEY_UP:
        rotate_block();
        break;
    }
}

void Game::finalize_block() {
    int position, trans_row, trans_col;
    for (position = 0; position < Block::s_num_cells; position++) {
        const auto& cell = m_block.get_cell(position);
        
        trans_row = cell.row + m_block.get_row_offset();
        trans_col = cell.col + m_block.get_col_offset();

        if (m_grid.is_off_grid(trans_row, trans_col) || !m_grid.is_cell_empty(trans_row, trans_col)) {
            m_game_over = true;
        }

        m_grid.set_cell_color(trans_row, trans_col, m_block.get_color_id());
    }

    if (!m_game_over) {
        m_block.clone(m_next_block);
        m_next_block.randomize();
    }

    int rows_cleared = m_grid.clear_full_rows();
    if (rows_cleared > 0) {
        m_sounds.play_clear();
        update_score(rows_cleared, 0);
    }
}

void Game::rotate_block() {
    m_block.rotate();
    if (is_block_touching_another_block_or_off_grid()) {
        m_block.undo_rotate();
    } else {
        m_sounds.play_rotate();
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
        finalize_block();
    }
}

bool Game::is_block_touching_another_block_or_off_grid() const {
    int position, trans_row, trans_col;
    for (position = 0; position < Block::s_num_cells; position++) {
        const auto& cell = m_block.get_cell(position);

        trans_row = cell.row + m_block.get_row_offset();
        trans_col = cell.col + m_block.get_col_offset();

        if (m_grid.is_off_grid(trans_row, trans_col) || !m_grid.is_cell_empty(trans_row, trans_col)) {
            return true;
        }
    }
    return false;
}

void Game::update_score(const int &rows_cleared, const int &down_points) {
    static const std::array<int, 5> rows_cleared_points = {0, 100, 300, 500, 1000};

    // Clamp to range between 0 and 4 (4 is max score points)
    const int clamped_rows_cleared = std::max(std::min(rows_cleared, 4), 0);
    
    m_score += rows_cleared_points[clamped_rows_cleared];
    m_score += down_points;

    if (clamped_rows_cleared == 4) {
        // TODO: play tetris sound
    }
}

void Game::reset_game() {
    m_game_over = false;
    m_score = 0;
    m_last_update_in_secs = 0.0;
    m_grid.reset_cells();
    m_block.randomize();
    m_next_block.randomize();
}

void Game::draw_score_time_and_preview_hud(const Vector2 &bounds) const {
    // Draw text to the right of the Tetris Grid
    s_text_buffer.bounds.x = (Grid::s_cell_size * Grid::s_num_cols) + Grid::s_padding + 10.0f;
    s_text_buffer.bounds.y = Grid::s_padding;
    DrawText("SCORE:", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 20, RED);

    s_text_buffer.bounds.y += 25.0f;
    DrawText(TextFormat("%d", m_score), s_text_buffer.bounds.x, s_text_buffer.bounds.y, 16, WHITE);

    s_text_buffer.bounds.y += 30.0f;
    DrawText("TIME:", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 20, RED);

    s_text_buffer.bounds.y += 25.0f;
    DrawText(TextFormat("%.2f", GetTime()), s_text_buffer.bounds.x, s_text_buffer.bounds.y, 16, WHITE);

    s_text_buffer.bounds.y += 30.0f;
    const float preview_outline_size = bounds.x - s_text_buffer.bounds.x - 10.0f;
    DrawRectangleLines(
        s_text_buffer.bounds.x,
        s_text_buffer.bounds.y,
        preview_outline_size,
        preview_outline_size,
        LIGHTGRAY
    );

    m_next_block.draw_preview({
        .x=s_text_buffer.bounds.x,
        .y=s_text_buffer.bounds.y,
        .height=preview_outline_size,
        .width=preview_outline_size
    });

    s_text_buffer.width = MeasureText("Next", 18);
    s_text_buffer.bounds.y += 5.0f;
    s_text_buffer.bounds.x += (preview_outline_size / 2.0f) - (s_text_buffer.width / 2.0f);
    DrawText("Next", 
        s_text_buffer.bounds.x,
        s_text_buffer.bounds.y,
        18,
        RED
    );
}

void Game::draw_not_started_hud(const Vector2 &bounds) const {
    s_text_buffer.width = MeasureText("Welcome!", 20);
    s_text_buffer.bounds.x = (bounds.x / 2.0f) - (s_text_buffer.width / 2.0f);
    s_text_buffer.bounds.y = (bounds.y / 2.0f) - 10.0f - 20.0f - 30.0f;
    DrawText("Welcome!", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 20, WHITE);

    s_text_buffer.width = MeasureText("Tetris Clone", 30);
    s_text_buffer.bounds.x = (bounds.x / 2.0f) - (s_text_buffer.width / 2.0f);
    s_text_buffer.bounds.y += 30.0f;
    DrawText("Tetris Clone", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 30, WHITE);

    s_text_buffer.width = MeasureText("Press 'enter' to play", 12 );
    s_text_buffer.bounds.x = (bounds.x / 2.0f) - (s_text_buffer.width / 2.0f);
    s_text_buffer.bounds.y += 60.0f;
    DrawText("Press 'enter' to play", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 12, WHITE);

    s_text_buffer.width = MeasureText("Powered by Suehr Gaming LLC", 10);
    s_text_buffer.bounds.x = (bounds.x / 2.0f) - (s_text_buffer.width / 2.0f);
    s_text_buffer.bounds.y = bounds.y - 30.0f;
    DrawText("Powered by Suehr Gaming LLC", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 10, WHITE);
}

void Game::draw_game_over_hud(const Vector2 &bounds) const {
    s_text_buffer.width = MeasureText("GAME OVER", 30);
    s_text_buffer.bounds.x = (bounds.x / 2.0f) - (s_text_buffer.width / 2.0f);
    s_text_buffer.bounds.y = 20.0f;
    DrawText("GAME OVER", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 30, RED);

    s_text_buffer.width = MeasureText("Press 'enter' to play again", 12);
    s_text_buffer.bounds.x = (bounds.x / 2.0f) - (s_text_buffer.width / 2.0f);
    s_text_buffer.bounds.y += 40.0f;
    DrawText("Press 'enter' to play again", s_text_buffer.bounds.x, s_text_buffer.bounds.y, 12, RED);
}
