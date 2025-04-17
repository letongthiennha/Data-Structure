#include "Icons.h"

Texture2D play;
Texture2D pauseIcon;
Texture2D home;
Texture2D undoIcon;
Texture2D redoIcon;
Texture2D fastforward;

//để sau initwindow trong main
void loadImages() {
    //cmake trêm mac là ../include còn cmake trên win là ../../include, k biết vistual studio thì sao
    Image playim = LoadImage("../include/play.png");
    Image pauseim = LoadImage("../include/pause.png");
    Image homeim = LoadImage("../include/home.png");
    Image undoim = LoadImage("../include/undo.png");
    Image redoim = LoadImage("../include/redo.png");
    Image fastforwardim = LoadImage("../include/fast-forward.png");
    play = LoadTextureFromImage(playim);
    pauseIcon = LoadTextureFromImage(pauseim);
    home = LoadTextureFromImage(homeim);
    fastforward = LoadTextureFromImage(fastforwardim);
    redoIcon = LoadTextureFromImage(redoim);
    undoIcon = LoadTextureFromImage(undoim);
}
void unloadImages() {
    UnloadTexture(play);
    UnloadTexture(pauseIcon);
    UnloadTexture(home);
    UnloadTexture(undoIcon);
    UnloadTexture(redoIcon);
}