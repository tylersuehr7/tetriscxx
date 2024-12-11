#include "sounds.hpp"

Sounds::Sounds():
    m_clear_sound(LoadSound("assets/clear.mp3")),
    m_rotate_sound(LoadSound("assets/rotate.mp3")),
    m_music(LoadMusicStream("assets/music.mp3")) {
}

Sounds::~Sounds() {
    stop_music();
    UnloadSound(m_clear_sound);
    UnloadSound(m_rotate_sound);
    UnloadMusicStream(m_music);
}

void Sounds::play_clear() const {
    PlaySound(m_clear_sound);
}

void Sounds::play_rotate() const {
    PlaySound(m_rotate_sound);
}

void Sounds::start_music() const {
    PlayMusicStream(m_music);
}

void Sounds::continue_music() const {
    UpdateMusicStream(m_music);
}

void Sounds::stop_music() const {
    StopMusicStream(m_music);
}
