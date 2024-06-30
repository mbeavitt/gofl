#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PADDING 2
#define CUBESIZE 10

//------------------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------------
void initialise_random(int num_rows, int num_cols, bool board[num_rows][num_cols]);
void print_board(int num_rows, int num_cols, bool board[num_rows][num_cols], Color draw_colour);
void game_step(int num_rows, int num_cols, bool board[num_rows][num_cols]);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    const int screenWidth = 700;
    const int screenHeight = 700;
    int draw_rate = 12;
    int num_rows = 4000 / (CUBESIZE);
    int num_cols = 4000 / (CUBESIZE);
    bool board[num_rows][num_cols];
    bool pause = false;
    int counter = 0;
    int colour_choice = 0;
    Color draw_colour = (Color) {255, 255, 255, 255};

    srand((unsigned) time(NULL));

    InitWindow(screenWidth, screenHeight, "The Game of Life");
    initialise_random(num_rows, num_cols, board);

    SetTargetFPS(120);               // Set our game to run at 120 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_R)) initialise_random(num_rows, num_cols, board);
        if (IsKeyPressed(KEY_DOWN) && draw_rate != 24) {
            draw_rate++;
        } 
        if (IsKeyPressed(KEY_UP) && draw_rate != 1) {
            draw_rate--;
            if (counter > 0) {
                counter--;
            }
        }

        if (IsKeyPressed(KEY_ONE)) draw_colour = RED;
        if (IsKeyPressed(KEY_TWO)) draw_colour = BLUE; 
        if (IsKeyPressed(KEY_THREE)) draw_colour = GREEN; 
        if (IsKeyPressed(KEY_FOUR)) draw_colour = YELLOW; 
        if (IsKeyPressed(KEY_FIVE)) draw_colour = ORANGE;
        if (IsKeyPressed(KEY_SIX)) draw_colour = PURPLE;
        if (IsKeyPressed(KEY_SEVEN)) draw_colour = PINK;
        if (IsKeyPressed(KEY_EIGHT)) draw_colour = WHITE;
        if (IsKeyPressed(KEY_NINE)) draw_colour = LIGHTGRAY;
        
        // check for alt + enter
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
        {
            // see what display we are on right now
            int display = GetCurrentMonitor();


            if (IsWindowFullscreen())
            {
                // if we are full screen, then go back to the windowed size
                SetWindowSize(screenWidth, screenHeight);
            }
            else
            {
                // if we are not full screen, set the window size to match the monitor we are on
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
            }

            // toggle the state
            ToggleFullscreen();
        }

        // choose to pause the animation
        if (GetKeyPressed() == 32) pause = !pause;

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);
            // draw board from 'board' variable
            print_board(num_rows, num_cols, board, draw_colour);

            // separate game steps from fps
            if (counter == draw_rate) {
                if (!pause) game_step(num_rows, num_cols, board);
                counter = 0;
            } else {
                counter++;
            }

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}


//------------------------------------------------------------------------------------
// Function definitions 
//------------------------------------------------------------------------------------
void initialise_random(int num_rows, int num_cols, bool board[num_rows][num_cols]) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if ((rand() % 5) == 0) {
                board[i][j] = 1;
            } else {
                board[i][j] = 0;
            }
        }
    }
}

void print_board(int num_rows, int num_cols, bool board[num_rows][num_cols], Color draw_colour) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (board[i][j] == 1) {
                DrawRectangle(i * CUBESIZE,
                             j * CUBESIZE,
                             CUBESIZE - PADDING,
                             CUBESIZE - PADDING,
                             draw_colour);
            }
        } 
    }
}

void game_step(int num_rows, int num_cols, bool board[num_rows][num_cols]) {
    int temp_board[num_rows][num_cols];
    int count;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            count = 0;
            if (j + 1 < num_cols && board[i][j + 1] == 1) count++;
            if (j - 1 >= 0 && board[i][j - 1] == 1) count++;
            if (i - 1 >= 0 && board[i - 1][j] == 1) count++;
            if (i + 1 < num_rows && board[i + 1][j] == 1) count++;
            if (i + 1 < num_rows && j + 1 < num_cols && board[i + 1][j + 1] == 1) count++;
            if (i - 1 >= 0 && j + 1 < num_cols && board[i - 1][j + 1] == 1) count++;
            if (i + 1 < num_rows && j - 1 >= 0 && board[i + 1][j - 1] == 1) count++;
            if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == 1) count++;
            temp_board[i][j] = count;
        }
    }
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            switch (temp_board[i][j]) {
                case 0: board[i][j] = 0; break;
                case 1: board[i][j] = 0; break;
                case 2: if (board[i][j] == 1) board[i][j] = 1; break;
                case 3: board[i][j] = 1; break;
                case 4: board[i][j] = 0; break;
                case 5: board[i][j] = 0; break;
                case 6: board[i][j] = 0; break;
                case 7: board[i][j] = 0; break;
                case 8: board[i][j] = 0; break;
            }
        }
    }
}
