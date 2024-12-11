#include "sounds.hpp"
#include <raylib.h>

static Sound s_clear_sound;
static Sound s_rotate_sound;
static Music s_music;

void Sounds::load_sounds() {
    s_clear_sound = LoadSound("assets/clear.mp3");
    s_rotate_sound = LoadSound("assets/rotate.mp3");
    s_music = LoadMusicStream("assets/music.mp3");
}

void Sounds::unload_sounds() {
    UnloadSound(s_clear_sound);
    UnloadSound(s_rotate_sound);
    UnloadMusicStream(s_music);
}

void Sounds::play_clear() {
    PlaySound(s_clear_sound);
}

void Sounds::play_rotate() {
    PlaySound(s_rotate_sound);
}

void start_music() {
    PlayMusicStream(s_music);
}

void continue_music() {
    UpdateMusicStream(s_music);
}

void stop_music() {
    StopMusicStream(s_music);
}
