#include <raylib.h>
#include "game.hpp"

constexpr const int WINDOW_WIDTH = 500;
constexpr const int WINDOW_HEIGHT = 640;

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TETRIS");

    Game game({(float) WINDOW_WIDTH, (float) WINDOW_HEIGHT});

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.on_update();
        BeginDrawing();
            ClearBackground(BLACK);
            game.on_render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
