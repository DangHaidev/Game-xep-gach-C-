#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include<chrono>

bool Paused = false;
bool gameEnded = false;
double totalRunTime = 0.0;
double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(860, 1100, "Game xếp gạchh");
    SetTargetFPS(60);
    auto startTime = std::chrono::high_resolution_clock::now();

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);



    Game game = Game();

    while (WindowShouldClose() == false)
    {
        if(IsKeyPressed(KEY_SPACE)){
            Paused = !Paused;
        }

    if(!Paused){
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
    }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {(2)*350, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {(2)*350, 175}, 38, 2, WHITE);
        if (!gameEnded &&game.gameOver)
        {
            gameEnded = true;
            auto endTime = std::chrono::high_resolution_clock::now();
            totalRunTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            totalRunTime /= 1000;

            // std::cout << "Total game run time: " << totalRunTime << " milliseconds" << std::endl;
            DrawTextEx(font, "GAME OVER", {(2)*320, 450}, 38, 2, WHITE);

        }
         if (gameEnded) {
            DrawText(TextFormat("Time: %.2f s", totalRunTime), 620, 580, 38, WHITE);
            DrawText("Bam Enter de \n   choi lai",624,690,30,WHITE);
        }
        if (IsKeyPressed(KEY_ENTER) && gameEnded) {
            // Reset thời gian
            totalRunTime = 0.0;

            // Reset trạng thái game và bất kỳ biến khác cần thiết
            gameEnded = false;
        }

        DrawRectangleRounded({(2)*320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {2*320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({(2)*320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();

        if(Paused){
            DrawText("Paused",210,450,40, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}