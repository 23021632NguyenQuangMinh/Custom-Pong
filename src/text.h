#ifndef _text__H_
#define _text__H_
#include<string>
void writeText(const char* s, int x, int y, int fsize){
    font = TTF_OpenFont("font/upheavtt.ttf", fsize);

    SDL_Rect dsrect;
    dsrect.x = x;
    dsrect.y = y;

    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, s, textColor);
    if (textSurface == NULL) {
        cout << "khong the khoi tao text surface! " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        cout << "khong the kgoi tao texture tu rendered text!" << SDL_GetError() << endl;
        return;
    }

    dsrect.w = textSurface->w;
    dsrect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_RenderCopy(renderer, textTexture, NULL, &dsrect);
    SDL_DestroyTexture(textTexture);
}

#endif 