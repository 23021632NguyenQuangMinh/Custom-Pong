#ifndef _engine__H_
#define _engine__H_

#include <math.h>
#include <algorithm>
#include "text.h"
#include<string>

struct object{
    SDL_Rect rect;
};

object Ball, Paddle1, Paddle2;

struct engine {


    //Setup cho game moi
    void ResetForNewGame() {
        PlayerScore1 = 0;
        PlayerScore2 = 0;

        Ball.rect.w = Ball_width;
        Ball.rect.h = Ball_height;

        Paddle1.rect.x = 0.0f;
        Paddle1.rect.y = (SCREEN_HEIGHT - Paddle_Height) / 2.0f;
        Paddle1.rect.w = Paddle_Width;
        Paddle1.rect.h = Paddle_Height;


        Paddle2.rect.x = SCREEN_WIDTH - Paddle_Width;
        Paddle2.rect.y = (SCREEN_HEIGHT - Paddle_Height) / 2;
        Paddle2.rect.w = Paddle_Width;
        Paddle2.rect.h = Paddle_Height;

    }

    //1player
    void OnePlayer() {
        run();
        CheckInputForOnePlayer();
    }

    //2player
    void TwoPlayer() {
        run();
        CheckInputForTwoPlayer();
    }

    // xu ly logic
    void Update() {
        if (PlayerScore1 == Max_Score) {
            writeText(GameOverText1, 350, 290, Message_FontSize);
            writeText(GameOverText, 140, 360, Message_FontSize - 10);
            SDL_RenderPresent(renderer);
            while (PlayerScore1 == Max_Score)
            {
                GameOver();
            }
        }
        if (PlayerScore2 == Max_Score) {
            writeText(GameOverText2, 350, 290, Message_FontSize);
            writeText(GameOverText, 140, 360, Message_FontSize - 10);
            SDL_RenderPresent(renderer);
            while (PlayerScore2 == Max_Score)
            {
                GameOver();
            }
        }

        Ball.rect.x += Ball_velo_x;
        Ball.rect.y += Ball_velo_y;

        Contact contact1 = checkBallPaddleCollision(Ball, Paddle1);
        Contact contact2 = checkBallPaddleCollision(Ball, Paddle2);
        Contact contact3 = checkWallBallCollision(Ball);

        if (contact1.Pos != CollisionPos::None) {
            CollideWithPaddle(contact1);
            playAudio(paddleHitSound);
        }
        else if (contact2.Pos != CollisionPos::None) {
            CollideWithPaddle(contact2);
            playAudio(paddleHitSound);
        }
        else if (contact3.Pos != CollisionPos::None) {
            CollideWithWall(contact3);
            playAudio(wallHitSound);
        }

        if (Ball.rect.x + 60 >= SCREEN_WIDTH) {
            playAudio(scoreSound);
            PlayerScore1++;
            ResetBallAndPaddle();
        }

        if (Ball.rect.x < 20) {
            playAudio(scoreSound);
            PlayerScore2++;
            ResetBallAndPaddle();
        }
        writeText(std::to_string(PlayerScore1).c_str(), SCREEN_WIDTH / 2 - Score_FontSize - 100, 20, Score_FontSize);
        writeText(std::to_string(PlayerScore2).c_str(), SCREEN_WIDTH / 2 + Score_FontSize + 50, 20, Score_FontSize);
        writeText(":", SCREEN_WIDTH / 2 - 5, 20, Score_FontSize);

    }

    void ResetBallAndPaddle() {

        Paddle1.rect.x = 0.0f;
        Paddle1.rect.y = (SCREEN_HEIGHT - Paddle_Height) / 2.0f;
        Paddle1.rect.w = Paddle_Width;
        Paddle1.rect.h = Paddle_Height;


        Paddle2.rect.x = SCREEN_WIDTH - Paddle_Width;
        Paddle2.rect.y = (SCREEN_HEIGHT - Paddle_Height) / 2;
        Paddle2.rect.w = Paddle_Width;
        Paddle2.rect.h = Paddle_Height;
        if (Ball.rect.x + 60 >= SCREEN_WIDTH) {
            Ball.rect.x = (SCREEN_WIDTH - Ball_width) / 2.0f + 300.0;
            Ball.rect.y = (SCREEN_HEIGHT - Ball_height) / 2.0f;
            if (Ball_velo_x > 0.0) {
                Ball_velo_x = -8.0f;
                Ball_velo_y = 0.0f;
            }
            else {
                Ball_velo_x = 8.0f;
                Ball_velo_y = 0.0f;
            }
        }

        if (Ball.rect.x < 20) {
            Ball.rect.x = (SCREEN_WIDTH - Ball_width) / 2.0f - 300.0;
            Ball.rect.y = (SCREEN_HEIGHT - Ball_height) / 2.0f;

            if (Ball_velo_x > 0) {
                Ball_velo_x = -8.0f;
                Ball_velo_y = 0.0f;
            }
            else {
                Ball_velo_x = 8.0f;
                Ball_velo_y = 0.0f;
            }
        }
    }


    // input 2 ng choi
    void CheckInputForTwoPlayer() {
        if (key_state[SDL_SCANCODE_W] and Paddle1.rect.y > 0) {
            Paddle1.rect.y -= Paddle_Velo;
        }

        if (key_state[SDL_SCANCODE_S] and Paddle1.rect.y < SCREEN_HEIGHT - Paddle1.rect.h) {
            Paddle1.rect.y += Paddle_Velo;
        }

        if (key_state[SDL_SCANCODE_UP] and Paddle2.rect.y > 0) {
            Paddle2.rect.y -= Paddle_Velo;
        }

        if (key_state[SDL_SCANCODE_DOWN] and Paddle2.rect.y < SCREEN_HEIGHT - Paddle2.rect.h) {
            Paddle2.rect.y += Paddle_Velo;
        }
    }

    // input 1 ng choi
    void CheckInputForOnePlayer() {
        if (key_state[SDL_SCANCODE_W] and Paddle1.rect.y > 0) {
            Paddle1.rect.y -= Paddle_Velo;
        }

        if (key_state[SDL_SCANCODE_S] and Paddle1.rect.y < SCREEN_HEIGHT - Paddle1.rect.h) {
            Paddle1.rect.y += Paddle_Velo;
        }

        if (Paddle2.rect.y + Paddle2.rect.h / 2 > Ball.rect.y + Ball.rect.h / 2 and Paddle2.rect.y > 0) {
            Paddle2.rect.y -= (Paddle_Velo + deltav);
        }
        if (Paddle2.rect.y + Paddle2.rect.h / 2 < Ball.rect.y + Ball.rect.h / 2 and Paddle2.rect.y + Paddle2.rect.h < SCREEN_HEIGHT) {
            Paddle2.rect.y += (Paddle_Velo + deltav);
        }

    }

    // kiem tra va cham
    Contact checkBallPaddleCollision(object ball, object paddle) {
        Contact contact = { CollisionPos::None, 0.0f };

        float ballLeft = ball.rect.x;
        float ballRight = ball.rect.x + ball.rect.w;
        float ballTop = ball.rect.y;
        float ballBottom = ball.rect.y + ball.rect.h;

        float paddleLeft = paddle.rect.x;
        float paddleRight = paddle.rect.x + paddle.rect.w;
        float paddleTop = paddle.rect.y;
        float paddleBottom = paddle.rect.y + paddle.rect.h;

        if (!(ballLeft >= paddleRight || ballRight <= paddleLeft || ballTop >= paddleBottom || ballBottom <= paddleTop)) {
            float paddleRangeUpper = paddleBottom - (2.0f * paddle.rect.h / 3.0f);
            float paddleRangeMiddle = paddleBottom - (paddle.rect.h / 3.0f);

            if (Ball_velo_x < 0) {
                contact.offset = paddleRight - ballLeft;
            }
            else if (Ball_velo_x > 0) {
                contact.offset = paddleLeft - ballRight;
            }

            if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper)) {
                contact.Pos = CollisionPos::Top;
            }
            else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle)) {
                contact.Pos = CollisionPos::Middle;
            }
            else {
                contact.Pos = CollisionPos::Bottom;
            }
        }
        return contact;
    }

    void CollideWithPaddle(Contact const& contact) {
        Ball.rect.x += contact.offset;
        if (abs(Ball_velo_x) < max_velo) {
            if (contact.Pos == CollisionPos::Top) {

                if (Ball_velo_x > 0) {
                    Ball_velo_x = -Ball_velo_x - accelaration;
                    Ball_velo_y = -1.0f * abs(Ball_velo_x) - accelaration;
                }
                else {
                    Ball_velo_x = -Ball_velo_x + accelaration;
                    Ball_velo_y = -1.0f * abs(Ball_velo_x + accelaration);

                }
            }

            else if (contact.Pos == CollisionPos::Middle) {
                if (Ball_velo_x > 0) {
                    Ball_velo_x = -Ball_velo_x - accelaration;
                }
                else {
                    Ball_velo_x = -Ball_velo_x + accelaration;
                }
            }

            else if (contact.Pos == CollisionPos::Bottom) {
                if (Ball_velo_x > 0) {
                    Ball_velo_x = -Ball_velo_x - accelaration;
                    Ball_velo_y = 1.0f * abs(Ball_velo_x - accelaration);
                }
                else {
                    Ball_velo_x = -Ball_velo_x + accelaration;
                    Ball_velo_y = 1.0f * abs(Ball_velo_x + accelaration);
                }

            }
        }

        else {
            if (contact.Pos == CollisionPos::Top) {

                Ball_velo_x = -Ball_velo_x;
                Ball_velo_y = -1.0f * abs(Ball_velo_x);
            }
            else if (contact.Pos == CollisionPos::Middle) {
                Ball_velo_x = -Ball_velo_x;
            }
            else if (contact.Pos == CollisionPos::Bottom) {
                Ball_velo_x = -Ball_velo_x;
                Ball_velo_y = 1.0f * abs(Ball_velo_x);
            }
        }
    }


    Contact checkWallBallCollision(object ball) {

        float ballLeft = ball.rect.x;
        float ballRight = ball.rect.x + ball.rect.w;
        float ballTop = ball.rect.y;
        float ballBottom = ball.rect.y + ball.rect.h;

        Contact contact{};

        if (ballTop < 0.0f) {
            contact.Pos = CollisionPos::Top;
            contact.offset = -ballTop;
        }

        else if (ballBottom > SCREEN_HEIGHT)
        {
            contact.Pos = CollisionPos::Bottom;
            contact.offset = SCREEN_HEIGHT - ballBottom;
        }

        return contact;

    }

    void CollideWithWall(Contact const& contact) {
        if ((contact.Pos == CollisionPos::Top)
            || (contact.Pos == CollisionPos::Bottom))
        {
            Ball.rect.y += contact.offset;
            Ball_velo_y = -Ball_velo_y;
        }
    }

   

    void run() {
        GetInput();
        
        if (event.type == SDL_QUIT) {
            quit();
        }
        SDL_RenderClear(renderer);
            renderTexture(SetMap[mapSelected], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            renderTexture(Player1Tx[mapSelected], Paddle1.rect.x, Paddle1.rect.y, Paddle_Width, Paddle_Height);
            renderTexture(Player2Tx[mapSelected], Paddle2.rect.x, Paddle2.rect.y, Paddle_Width, Paddle_Height);
            renderTexture(SetBall[mapSelected], Ball.rect.x, Ball.rect.y, Ball.rect.w, Ball.rect.h);
        Update();
        SDL_RenderPresent(renderer);
    }

   


    //over
    void GameOver(){
        GetInput();
        if (key_state[SDL_SCANCODE_BACKSPACE]){
            ResetForNewGame();
            GameState = MainMenu;
        }

        if (key_state[SDL_SCANCODE_RETURN]and GameState==TwoPlayerMode){
            ResetForNewGame();
            GameState = TwoPlayerMode;
        }

        if (key_state[SDL_SCANCODE_RETURN]and GameState ==OnePlayerMode){
            ResetForNewGame();
            GameState = OnePlayerMode;
        }

    }
};

#endif // _engine__H_
