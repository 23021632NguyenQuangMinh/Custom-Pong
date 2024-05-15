#include <iostream>
#include <SDL.h>
#include <math.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "globalValue.h"
#include "menu.h"
#include "graphic.h"
#include "engine.h"

using namespace std;

int main(int argc, char* argv[]) {

    InitData();

    if (TTF_Init() == -1) {
        cout << "khong the khoi tao ttf!" << TTF_GetError();
    }

    initSound();
   

    menu GameMenu;

    engine GameEngine;

    Mix_PlayMusic(music[0], -1);

    while (true){
        SDL_RenderPresent(renderer);
        GetInput();

        switch (GameState){
        case MainMenu: {
            while (GameState == MainMenu) {
                GameMenu.loadMainMenu();
            }
            break;
        }
        case OptionsMenu: {
            while (GameState == OptionsMenu) {
                GameMenu.loadConfigMenu();
            }
            break;
        }
        case SelectionMenu: {
            while (GameState == SelectionMenu) {
                GameMenu.loadSelectionMenu();
            }
            break;
        }
                  
        case ChooseDifficulty: {
            while (GameState == ChooseDifficulty) {
                GameMenu.loadChooseDifficulty();
            }
            break;
        }
        case OnePlayerMode: {

            GameEngine.ResetBallAndPaddle();
            GameEngine.ResetForNewGame();
            while (GameState == OnePlayerMode) GameEngine.OnePlayer();
            break;

        }
        case TwoPlayerMode: {

            GameEngine.ResetBallAndPaddle();
            GameEngine.ResetForNewGame();
            while (GameState == TwoPlayerMode) {
                GameEngine.TwoPlayer();
            }
            break;
        }
        }
    }
    return 0;
}
