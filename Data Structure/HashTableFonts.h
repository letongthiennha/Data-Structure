#pragma once

#include "raylib.h"

class Fonts {
public:
    Fonts();
    ~Fonts();

    static bool fontsLoaded;
    static Font FuturaMedium;
    static Font FuturaBold;

    static void loadFonts();
    static void unloadFonts();
    static bool areFontsLoaded();
};