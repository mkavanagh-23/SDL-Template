#ifndef SETTINGS_H
#define SETTINGS_H

#include <string_view>

namespace Settings {
    constexpr int SCREEN_WIDTH = 800;   //Game screen width
    constexpr int SCREEN_HEIGHT = 600;  //Game screen height

    //Animation
    constexpr int FPS = 30;                 //Frame per second

    //Background Music
    constexpr std::string_view BG_MUSIC{"relative/path/to/music.wav"};
};

#endif