#include "Font.h"

Font FuturaMedium;
Font FuturaBold;
Font arial;

void loadFonts() {
    arial = LoadFont("../include/arial.ttf");
    FuturaMedium = LoadFont("../include/FuturaMedium.ttf");
    FuturaBold = LoadFont("../include/FuturaBold.ttf");
    SetTextureFilter(FuturaMedium.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(FuturaBold.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);
}

bool areFontsLoaded() {
    return arial.texture.id != 0 && FuturaMedium.texture.id != 0 && FuturaBold.texture.id != 0;
}

void unloadFonts() {
    UnloadFont(arial);
    UnloadFont(FuturaMedium);
    UnloadFont(FuturaBold); 
}