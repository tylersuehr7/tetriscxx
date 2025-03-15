#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include <raylib.h>
#include "grid.hpp"
#include "block.hpp"
#include "sounds.hpp"

namespace tetris {

class Game {
private:
    const Sounds& m_sounds;
    bool m_started{false};
    bool m_game_over{false};
    float m_game_speed{0.4f};
    double m_last_update_in_secs{0.0};
    int m_score{0};
    Grid m_grid{};
    Block m_block;
    Block m_next_block;
public:
    Game(const Sounds &sounds);
    void on_update();
    void on_render();
private:
    void finalize_block();
    void rotate_block();
    void move_block_left();
    void move_block_right();
    void move_block_down();
    bool is_block_touching_another_block_or_off_grid() const;
    void update_score(const int &rows_cleared, const int &down_points);
    void reset_game();
    void on_process_input();
    void draw_score_time_and_preview_hud(const Vector2 &bounds) const;
    void draw_not_started_hud(const Vector2 &bounds) const;
    void draw_game_over_hud(const Vector2 &bounds) const;
};

}

#endif//TETRIS_GAME_HPP