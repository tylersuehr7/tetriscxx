#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include <raylib.h>
#include "grid.hpp"
#include "block.hpp"
#include "sounds.hpp"

class Game {
private:
    const Vector2 m_size;
    const Sounds& m_sounds;
    bool m_started;
    bool m_game_over;
    float m_game_speed;
    double m_last_update_in_secs;
    int m_score;
    Grid m_grid;
    Block m_block;
    Block m_next_block;
public:
    Game(const Vector2 &size, const Sounds &sounds);
    void on_process_input();
    void on_update();
    void on_render();
private:
    void finalize_block();
    void rotate_block();
    void move_block_left();
    void move_block_right();
    void move_block_down();
    bool is_block_touching_another_block_or_off_grid();
    void update_score(const int &rows_cleared, const int &down_points);
    void reset_game();
    void draw_hud();
};

#endif//TETRIS_GAME_HPP