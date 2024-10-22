#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>
#include <string_view>
#include <string>

//Enum type to refer to movement directions by name
enum Direction {
  up,       // == 0
  right,    // == 1
  down,     // == 2
  left,     // == 3
  still     // == 4
};

//Enum type to hold R,G,B color values as one object (default white)
struct RGB {
    uint8_t r{255};
    uint8_t g{255};
    uint8_t b{255};
};

RGB HexToRGB(const std::string& hex);                   //Convert hex color codes to RGB color object

namespace Settings {
    
    constexpr int SCREEN_WIDTH = 800;   //Game screen width
    constexpr int SCREEN_HEIGHT = 600;  //Game screen height
    const std::string TITLE{"Game Title"};

    //Animation
    constexpr int FPS = 30;                 //Frame per second

    //Background Music
    constexpr std::string_view BG_MUSIC{"relative/path/to/music.wav"};

};

#endif