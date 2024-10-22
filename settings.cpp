#include <cstdint>
#include <cassert>
#include <string>
#include "settings.h"

RGB HexToRGB(const std::string& hex) {
    //Create temporary color objects
    std::string hexColor = hex;
    assert(hexColor.length() == 6 && "Provided colorKey not a color valid hex code.\n");
    RGB rgbColor;

    //Extract sets of two characters and convert to RGB values
    rgbColor.r = static_cast<uint8_t>(std::stoi(hexColor.substr(0,2), nullptr, 16));
    rgbColor.g = static_cast<uint8_t>(std::stoi(hexColor.substr(2,2), nullptr, 16));
    rgbColor.b = static_cast<uint8_t>(std::stoi(hexColor.substr(4,2), nullptr, 16));

    return rgbColor;
}