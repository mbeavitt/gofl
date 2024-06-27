#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define PADDING 2
#define CUBESIZE 10
#define NAVBAR_OFFSET 5
#define BLANK_CHAR ' '

//------------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------------
void initialise_random(int num_rows, int num_cols, char board[num_rows][num_cols], char input);
void print_board(int num_rows, int num_cols, char board[num_rows][num_cols]);
void game_step(int num_rows, int num_cols, char board[num_rows][num_cols], char key);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    const int screenWidth = 1440;
    const int screenHeight = 900;
    int num_rows = screenWidth / (CUBESIZE);
    int num_cols = -NAVBAR_OFFSET + screenHeight / (CUBESIZE);
    char board[num_rows][num_cols];

    srand((unsigned) time(NULL));

    InitWindow(screenWidth, screenHeight, "The Game of Life");
    initialise_random(num_rows, num_cols, board, 'o');

    SetTargetFPS(10);               // Set our game to run at 10 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);
            // draw board from 'board' variable
            print_board(num_rows, num_cols, board);
            game_step(num_rows, num_cols, board, 'o');

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}


//------------------------------------------------------------------------------------
// Function definitions 
//------------------------------------------------------------------------------------
void initialise_random(int num_rows, int num_cols, char board[num_rows][num_cols], char input) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if ((rand() % 5) == 0) {
                board[i][j] = input;
            } else {
                board[i][j] = ' ';
            }
        }
    }
}

void print_board(int num_rows, int num_cols, char board[num_rows][num_cols]) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (board[i][j] == 'o') {
                DrawRectangle(i * CUBESIZE,
                             j * CUBESIZE,
                             CUBESIZE - PADDING,
                             CUBESIZE - PADDING,
                             WHITE);
            }
        } 
    }
}

void game_step(int num_rows, int num_cols, char board[num_rows][num_cols], char key) {
    char temp_board[num_rows][num_cols];
    int count;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            count = 0;
            if (j + 1 < num_cols && board[i][j + 1] == key) count++;
            if (j - 1 >= 0 && board[i][j - 1] == key) count++;
            if (i - 1 >= 0 && board[i - 1][j] == key) count++;
            if (i + 1 < num_rows && board[i + 1][j] == key) count++;
            if (i + 1 < num_rows && j + 1 < num_cols && board[i + 1][j + 1] == key) count++;
            if (i - 1 >= 0 && j + 1 < num_cols && board[i - 1][j + 1] == key) count++;
            if (i + 1 < num_rows && j - 1 >= 0 && board[i + 1][j - 1] == key) count++;
            if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == key) count++;
            temp_board[i][j] = count;
        }
    }
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            switch (temp_board[i][j]) {
                case 0: board[i][j] = BLANK_CHAR; break;
                case 1: board[i][j] = BLANK_CHAR; break;
                case 2: if (board[i][j] == key) board[i][j] = key; break;
                case 3: board[i][j] = key; break;
                case 4: board[i][j] = BLANK_CHAR; break;
                case 5: board[i][j] = BLANK_CHAR; break;
                case 6: board[i][j] = BLANK_CHAR; break;
                case 7: board[i][j] = BLANK_CHAR; break;
                case 8: board[i][j] = BLANK_CHAR; break;
            }
        }
    }
}
