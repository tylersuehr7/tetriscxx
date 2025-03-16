#ifndef TETRIS_SOUNDS_HPP
#define TETRIS_SOUNDS_HPP

#include <raylib.h>

namespace tetris {

class Sounds {
private:
    Sound m_clear_sound;
    Sound m_rotate_sound;
    Music m_music;
public:
    Sounds();
    ~Sounds();

    // Sound resources should never be copied
    Sounds(const Sounds&) = delete;
    Sounds& operator=(const Sounds&) = delete;

    // Move semantics
    Sounds(Sounds&& other) noexcept;
    Sounds& operator=(Sounds&& other) noexcept;
    
    void play_clear() const;
    void play_rotate() const;
    void start_music() const;
    void continue_music() const;
    void stop_music() const;
};

}

#endif//TETRIS_SOUNDS_HPP