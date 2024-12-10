#ifndef TETRIS_GRID_HPP
#define TETRIS_GRID_HPP

#include <raylib.h>

class Grid {
public:
    typedef enum : unsigned char {
        COLOR_ID_EMPTY = 0,  // Empty Block
        COLOR_ID_BLUE,       // J Block
        COLOR_ID_GREEN,      // L Block
        COLOR_ID_ORANGE,     // I Block
        COLOR_ID_YELLOW,     // O Block
        COLOR_ID_LIGHTBLUE,  // T Block
        COLOR_ID_PURPLE,     // S Block
        COLOR_ID_RED,        // Z Block
        COLOR_ID_MAX
    } ColorId;
public:
    static constexpr const int s_num_rows     = 20;
    static constexpr const int s_num_cols     = 10;
    static constexpr const int s_padding      = 20;
    static constexpr const int s_cell_size    = 30;
    static constexpr const int s_cell_margin  = 1;
    static constexpr const Color s_cell_colors[COLOR_ID_MAX] = {
        LIGHTGRAY,  // COLOR_ID_EMPTY
        BLUE,       // COLOR_ID_BLUE
        GREEN,      // COLOR_ID_GREEN
        ORANGE,     // COLOR_ID_ORANGE
        YELLOW,     // COLOR_ID_YELLOW
        SKYBLUE,    // COLOR_ID_LIGHTBLUE
        PURPLE,     // COLOR_ID_PURPLE
        MAROON,     // COLOR_ID_RED
    };
private:
    ColorId m_cells[s_num_rows][s_num_cols];
public:
    Grid();
    void draw();
    void reset_cells();
    void set_cell_color(const unsigned int &row, const unsigned int &col, const ColorId &id);
};

#endif//TETRIS_GRID_HPP