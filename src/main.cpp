#include <raylib.h>
#include "game.hpp"
#include "sounds.hpp"

constexpr const int WINDOW_WIDTH = 500;
constexpr const int WINDOW_HEIGHT = 640;
constexpr const int FPS = 60;

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
    SetTargetFPS(FPS);
    InitAudioDevice();

    tetris::Sounds sounds;
    tetris::Game game(sounds);

    sounds.start_music();
    while (!WindowShouldClose()) {
        sounds.continue_music();
        game.on_update();
        BeginDrawing();
            game.on_render();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
