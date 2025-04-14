#include "HashTableFonts.h"


Font Fonts::FuturaBold;
Font Fonts::FuturaMedium;
bool Fonts::fontsLoaded;

void Fonts::loadFonts() {
    FuturaMedium = LoadFont("../../fonts/FuturaMedium.ttf");
    FuturaBold = LoadFont("../fonts/FuturaBold.ttf");
    SetTextureFilter(FuturaMedium.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(FuturaBold.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);
}
void Fonts::unloadFonts() {
    UnloadFont(FuturaMedium);
    UnloadFont(FuturaBold);   
}

bool Fonts::areFontsLoaded() {
    return Fonts::FuturaMedium.texture.id != 0 && Fonts::FuturaBold.texture.id != 0;
}

