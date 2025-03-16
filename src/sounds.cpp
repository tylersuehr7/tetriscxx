#include "sounds.hpp"

using namespace tetris;

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

Sounds::Sounds(Sounds&& other) noexcept :
    m_clear_sound(other.m_clear_sound),
    m_rotate_sound(other.m_rotate_sound),
    m_music(other.m_music) {
    // Zero out the other object's members to prevent double deletion
    other.m_clear_sound = {};
    other.m_rotate_sound = {};
    other.m_music = {};
}

Sounds& Sounds::operator=(Sounds&& other) noexcept {
    if (this != &other) {
        // Clean up existing resources
        stop_music();
        UnloadSound(m_clear_sound);
        UnloadSound(m_rotate_sound);
        UnloadMusicStream(m_music);
        
        // Move resources from other
        m_clear_sound = other.m_clear_sound;
        m_rotate_sound = other.m_rotate_sound;
        m_music = other.m_music;
        
        // Zero out the other object's members
        other.m_clear_sound = {};
        other.m_rotate_sound = {};
        other.m_music = {};
    }
    return *this;
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
