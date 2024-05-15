#pragma once
#ifndef _graphic__H_
#define _graphic__H_


SDL_Texture* loadTexture(const char* path){
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    
    if (texture == NULL) {
        cout << "Loi khoi tao texture!" << SDL_GetError() << endl;
    }
    return texture;
}
void loadMedia(){

    int flags=IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    if (!IMG_Init(flags)){
        cout << " Khong the khoi tao SDL_image!" << IMG_GetError;
        return;
    }

    MainMenuTexture = loadTexture("img/menu/menu.jpg");
    SelectionMenuTexture = loadTexture("img/menu/menu.selectmode.jpg");
    ChooseDifficultyTexture = loadTexture("img/menu/choosedifficulty.jpg");
    OptionsMenuTexture = loadTexture("img/menu/menu.options.jpg");
    MapSelectTexture = loadTexture("img/menu/map.jpg");
    HTPTexture = loadTexture("img/menu/HowToPlay.jpg");
    SoundConfigTexture = loadTexture("img/menu/menu.soundconfig.jpg");
    EndPiece1 = loadTexture("img/menu/EndPiece.png");
    EndPiece2 = loadTexture("img/menu/EndPiece.png");
    MidPart = loadTexture("img/menu/MidPart.png");

    SetMap[0] = loadTexture("img/backgrounds/bongda.png");
    SetMap[1] = loadTexture("img/backgrounds/bongro.jpg");
    SetMap[2] = loadTexture("img/backgrounds/tennis.jpg");

    SetBall[0] = loadTexture("img/balls/quabongda.png");
    SetBall[1] = loadTexture("img/balls/quabongro.png");
    SetBall[2] = loadTexture("img/balls/quatennis.png");

    Player1Tx[0] = loadTexture("img/paddles/ronaldo.png");
    Player1Tx[1] = loadTexture("img/paddles/curry.png");
    Player1Tx[2] = loadTexture("img/paddles/nadal.png");
    Player2Tx[0] = loadTexture("img/paddles/messi.png");
    Player2Tx[1] = loadTexture("img/paddles/lebron.png");
    Player2Tx[2] = loadTexture("img/paddles/novak.png");

}
void InitData(){
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        cout << "SDL khong the khoi tao!" << SDL_GetError();
        return;
    }

    g_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        cout << "khong the tao g_window!" << SDL_GetError();
        return;
    }
    else {
        renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        loadMedia();
    }
}
void renderTexture(SDL_Texture* texture, int x, int y, int w, int h){
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}


#endif // _graphic__H_