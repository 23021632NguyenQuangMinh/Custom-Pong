#ifndef _globalValue__H_
#define _globalValue__H_

using namespace std;

// Game window
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const char* WINDOW_TITLE = "Custom Pong game";



const Uint8* key_state = SDL_GetKeyboardState(nullptr);

SDL_Window* g_window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;
SDL_Point MousePoint;
// Mouse held down
bool mouseHeld = false;

//Textures

SDL_Texture* MainMenuTexture = nullptr;
SDL_Texture* OptionsMenuTexture = nullptr;
SDL_Texture* SelectionMenuTexture = nullptr;
SDL_Texture* ChooseDifficultyTexture = nullptr;
SDL_Texture* MapSelectTexture = nullptr;
SDL_Texture* HTPTexture = nullptr;
SDL_Texture* SoundConfigTexture = nullptr;
SDL_Texture* EndPiece1 = nullptr;
SDL_Texture* EndPiece2 = nullptr;
SDL_Texture* MidPart = nullptr;
SDL_Texture* SetMap[3] = { nullptr };
SDL_Texture* SetBall[3] = { nullptr };
SDL_Texture* Player1Tx[3] = { nullptr };
SDL_Texture* Player2Tx[3] = { nullptr };
// Audio
Mix_Chunk* scoreSound;
Mix_Chunk* buttonClickedSound;
Mix_Chunk* wallHitSound;
Mix_Chunk* paddleHitSound;
Mix_Music* music[5];


enum CollisionPos
{
    None,
    Top,
    Middle,
    Bottom
};


struct Contact
{
    CollisionPos Pos;
    float offset;
};


// object size/speed
const int Ball_width = 40;
const int Ball_height = 40;
const int Paddle_Width = 120;
const int Paddle_Height = 100;
const int Paddle_Velo = 9.0f;
int Ball_velo_x = 8.0f;
int Ball_velo_y = 0;


// gia toc and v max
int accelaration = 1.0f;
int max_velo = 20.0f;

//thong diep
const char* GameOverText1 = " Player 1 won the match! ";
const char* GameOverText2 = " Player 2 won the match! ";
const char* GameOverText = " Press Enter to replay or BackSpace to return";
const char* songName[5] = { "Duck","Monkey","Peeker","Run","Sneaky" };


//font
TTF_Font* font;

// co chu cua diem so/ thong diep
const int Score_FontSize = 70;
const int Message_FontSize = 50;

// diem toi da
const int Max_Score = 3;


// GameState Deffinitions
const int MainMenu = 0;
const int OptionsMenu = 1;
const int SelectionMenu = 2;
const int OnePlayerMode = 3;
const int ChooseDifficulty = 4;
const int TwoPlayerMode = 5;



const int MapSelect = 2;
const int HTP = 3;
const int SoundConfig = 4;

const int EasyMode = 5;
const int MediumMode = 6;
const int HardMode = 7;
const int InsaneMode = 8;

// Current State
int GameState = MainMenu;
int OptionsState = OptionsMenu;
int DifficultyState = ChooseDifficulty;
int deltav = 0.0f;

//config
int Volume = 100;
int SongSelected = 0;
int mapSelected = 0;

//score
int PlayerScore1 = 0;
int PlayerScore2 = 0;

//mouse
int xMouse, yMouse;

// Lay input
void GetInput(){
    SDL_PollEvent(&event);
    SDL_GetMouseState(&xMouse, &yMouse);
    MousePoint = { xMouse, yMouse };
}

// thoat
void quit(){
    SDL_DestroyTexture(MainMenuTexture);
    SDL_DestroyTexture(OptionsMenuTexture);
    SDL_DestroyTexture(ChooseDifficultyTexture);
    SDL_DestroyTexture(SelectionMenuTexture);
    SDL_DestroyTexture(MapSelectTexture);
    SDL_DestroyTexture(HTPTexture);
    SDL_DestroyTexture(SoundConfigTexture);
    SDL_DestroyTexture(EndPiece1);
    SDL_DestroyTexture(EndPiece2);
    SDL_DestroyTexture(MidPart);
    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(SetMap[i]);
        SDL_DestroyTexture(SetBall[i]);
        SDL_DestroyTexture(Player1Tx[i]);
        SDL_DestroyTexture(Player2Tx[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(g_window);
    Mix_FreeChunk(scoreSound);
    Mix_FreeChunk(buttonClickedSound);
    Mix_FreeChunk(wallHitSound);
    Mix_FreeChunk(paddleHitSound);
    for (int i = 0; i < 5; i++) {
        Mix_FreeMusic(music[i]);
    }
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

}

#endif // _globalValue__H_
