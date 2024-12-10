#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP

#include <raylib.h>

class Game {
private:
    const Vector2 m_size;
public:
    Game(const Vector2 &size);
    void on_process_input();
    void on_update();
    void on_render();
};

#endif//TETRIS_GAME_HPP