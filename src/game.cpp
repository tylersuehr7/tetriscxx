#include "game.hpp"

Game::Game(const Vector2 &size): m_size(size), m_grid(Grid()) {
}

void Game::on_process_input() {

}

void Game::on_update() {

}

void Game::on_render() {
    ClearBackground(BLACK);
    m_grid.draw();
}
