#include <raylib.h>
#include "game.hpp"
#include "sounds.hpp"

constexpr const int WINDOW_WIDTH = 500;
constexpr const int WINDOW_HEIGHT = 640;

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TETRIS");
    InitAudioDevice();

    Sounds sounds;

    Game game({(float) WINDOW_WIDTH, (float) WINDOW_HEIGHT}, sounds);

    SetTargetFPS(60);

    sounds.start_music();
    while (!WindowShouldClose()) {
        sounds.continue_music();
        game.on_process_input();
        game.on_update();
        BeginDrawing();
            ClearBackground(BLACK);
            game.on_render();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
