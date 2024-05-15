#ifndef _Menu__H_
#define _Menu__H_
#include "graphic.h"
#include "sound.h"
#include "text.h"
struct menu
{
    // Main menu
    void loadMainMenu(){
        GetInput();
        SDL_RenderClear(renderer);
        renderTexture(MainMenuTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Rect PlayButtonRect = { 505,395,275,75 };
        SDL_Rect ConfigButtonRect = { 505,495,265,75 };
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_PointInRect(&MousePoint, &PlayButtonRect))
            {
                playAudio(buttonClickedSound);
                GameState = SelectionMenu;
            }
            if (SDL_PointInRect(&MousePoint, &ConfigButtonRect))
            {
                playAudio(buttonClickedSound);
                GameState = OptionsMenu;
            }
        }
        if (key_state[SDL_SCANCODE_ESCAPE] or event.type==SDL_QUIT) quit();
        SDL_RenderPresent(renderer);
    }
    // Chon mode 1 vs 2 ng choi
    void loadSelectionMenu(){
        GetInput();
        SDL_RenderClear(renderer);
        renderTexture(SelectionMenuTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Rect OnePlayerRect = { 475,175,335,95 };
        SDL_Rect TwoPlayerRect = { 475,345,335,95 };
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_PointInRect(&MousePoint, &OnePlayerRect))
            {
                playAudio(buttonClickedSound);
                GameState = ChooseDifficulty;
            }
            if (SDL_PointInRect(&MousePoint, &TwoPlayerRect))
            {
                playAudio(buttonClickedSound);
                GameState = TwoPlayerMode;
            }
        }
        if (key_state[SDL_SCANCODE_BACKSPACE]) {
            GameState = MainMenu;
        }
        if (event.type == SDL_QUIT) {
            quit();
        }
        SDL_RenderPresent(renderer);

    }

    void loadChooseDifficulty() {
        GetInput();
        SDL_RenderClear(renderer);
        renderTexture(ChooseDifficultyTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Rect EasyRect = { 490,160,340,100 };
        SDL_Rect MediumRect = { 490,270,340,100 };
        SDL_Rect HardRect = { 490,390,340,100 };
        SDL_Rect InsaneRect = {490,510,340,100};
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_PointInRect(&MousePoint, &EasyRect)){
                playAudio(buttonClickedSound);
                DifficultyState = EasyMode;
            }
            if (SDL_PointInRect(&MousePoint, &MediumRect))
            {
                playAudio(buttonClickedSound);
                DifficultyState = MediumMode;
            }
            if (SDL_PointInRect(&MousePoint, &HardRect))
            {
                playAudio(buttonClickedSound);
                DifficultyState = HardMode;
            }

            if (SDL_PointInRect(&MousePoint, &InsaneRect))
            {
                playAudio(buttonClickedSound);
                DifficultyState = InsaneMode;
            }

        }
        switch (DifficultyState) {
            case EasyMode: {
                if (Ball_velo_x < 10.0f) {
                    deltav = -1.5f;
                }

                if (Ball_velo_x < 14.0f) {
                    deltav = -1.0f;
                }
                
                else {
                    deltav = 0.0f;
                }
                
                GameState = OnePlayerMode;
                break;
            }
            case MediumMode:{
                if (Ball_velo_x < 10.0f) {
                    deltav = 0.0f;
                }

                if (Ball_velo_x < 14.0f) {
                    deltav = 1.0f;
                }

                else {
                    deltav = 2.0f;
                }
                GameState = OnePlayerMode;
                break;
            }
            case HardMode:{
                if (Ball_velo_x < 10.0f) {
                    deltav = 2.0f;
                }

                if (Ball_velo_x < 14.0f) {
                    deltav = 3.0f;
                }

                else {
                    deltav = 4.0f;
                }
                GameState = OnePlayerMode;
                break;
            }
            case InsaneMode: {
                if (Ball_velo_x < 10.0f) {
                    deltav = 3.5f;
                }

                if (Ball_velo_x < 14.0f) {
                    deltav = 4.5f;
                }

                else {
                    deltav = 5.5f;
                }
                GameState = OnePlayerMode;
                break;
            }

        }
        if (key_state[SDL_SCANCODE_BACKSPACE]) {
            GameState = MainMenu;
        }

        if (key_state[SDL_SCANCODE_ESCAPE] or event.type == SDL_QUIT) {
            quit();
        }
        SDL_RenderPresent(renderer);
    }
    // Setting Menu
    void loadConfigMenu(){
        GetInput();
        SDL_RenderClear(renderer);
        SDL_Rect MapSelectRect = { 405,175,490,80 };
        SDL_Rect HTPRect = { 405,325,490,80 };
        SDL_Rect SoundConfigRect = { 405,460,490,80 };
        if (event.type == SDL_MOUSEBUTTONDOWN and OptionsState == OptionsMenu)
        {
            if (SDL_PointInRect(&MousePoint, &MapSelectRect))
            {
                playAudio(buttonClickedSound);
                OptionsState = MapSelect;
            }
            if (SDL_PointInRect(&MousePoint, &HTPRect))
            {
                playAudio(buttonClickedSound);
                OptionsState = HTP;
            }
            if (SDL_PointInRect(&MousePoint, &SoundConfigRect))
            {
                playAudio(buttonClickedSound);
                OptionsState = SoundConfig;
            }
        }
        switch (OptionsState){

            case OptionsMenu:{
            renderTexture(OptionsMenuTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            if (key_state[SDL_SCANCODE_BACKSPACE] and event.type == SDL_KEYDOWN) GameState = MainMenu;
            break;
            }

            case MapSelect:{
            loadMapSelect();
            break;
            }

            case HTP:{
            loadHTP();
            break;
            }

            case SoundConfig:{
            loadSoundConfig();
            break;
            }
        }
        if (key_state[SDL_SCANCODE_ESCAPE] or event.type == SDL_QUIT) {
            quit();
        }
        SDL_RenderPresent(renderer);

    }
    // Chon map
    void loadMapSelect(){
        renderTexture(MapSelectTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Rect Map1Rect = { 405,175,490,80 };
        SDL_Rect Map2Rect = { 405,325,490,80 };
        SDL_Rect Map3Rect = { 405,460,490,80 };
        if (event.type == SDL_MOUSEBUTTONDOWN){

            if (SDL_PointInRect(&MousePoint, &Map1Rect)){
                mapSelected = 0;
                playAudio(buttonClickedSound);
            }

            if (SDL_PointInRect(&MousePoint, &Map2Rect)){
                mapSelected = 1;
                playAudio(buttonClickedSound);
            }

            if (SDL_PointInRect(&MousePoint, &Map3Rect)){
                mapSelected = 2;
                playAudio(buttonClickedSound);
            }

        }

        if (key_state[SDL_SCANCODE_BACKSPACE]) {
            OptionsState = OptionsMenu;
        }

        if (key_state[SDL_SCANCODE_ESCAPE] or event.type == SDL_QUIT) {
            quit();
        }
    }
    // how to play
    void loadHTP(){
        renderTexture(HTPTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (key_state[SDL_SCANCODE_BACKSPACE]) {
            OptionsState = OptionsMenu;
        }
    }
    // audio
    void loadSoundConfig(){
        renderTexture(SoundConfigTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        renderTexture(MidPart, 600, 170, Volume * 2, 100);
        renderTexture(EndPiece1, 600, 170, 50, 100);
        renderTexture(EndPiece2, 600 + Volume * 2, 170, 50, 100);
        writeText(songName[SongSelected], 785, 365, 60);
        SDL_Rect EndPiece2Rect = { 600 + Volume * 2, 170 ,50,100 };
        if (key_state[SDL_SCANCODE_BACKSPACE]) {
            OptionsState = OptionsMenu;
        }
        SDL_Rect SongSelect = { 785, 365, 340, 100 };
        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (SDL_PointInRect(&MousePoint, &SongSelect)){
                if (SongSelected < 4) SongSelected++;
                else SongSelected = 0;
                changeSong();
            }
            if (SDL_PointInRect(&MousePoint, &EndPiece2Rect) and (event.button.button == SDL_BUTTON_LEFT)) {
                mouseHeld = true;
            }

        }
        if (mouseHeld)
        {
            if (xMouse > 600 + Volume * 2 and Volume < 240) Volume ++;
            else if (xMouse < 600 + Volume * 2 and Volume > 0) Volume--;
        }
        if (event.type == SDL_MOUSEBUTTONUP and (event.button.button == SDL_BUTTON_LEFT)) {
            mouseHeld = false;
        }
        if ( event.type == SDL_QUIT) {
            quit();
        }
        updateVolume();
    }
};

#endif // _Menu__H_