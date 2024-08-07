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
static Vector2 *SelectedCube = NULL;
const int screenWidth = 700;
const int screenHeight = 700;
//------------------------------------------------------------------------------------
// Function prototypes
//------------------------------------------------------------------------------------
void ranzomise_board(int num_rows, int num_cols, bool board[num_rows][num_cols]);
void clear_board(int num_rows, int num_cols, bool board[num_rows][num_cols]);
void print_board(int num_rows, int num_cols, bool board[num_rows][num_cols], Color draw_colour);
void game_step(int num_rows, int num_cols, bool board[num_rows][num_cols]);
void check_fullscreen(void);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    int draw_rate = 12;
    // TODO: dynamically change game state matrix based on current window size
    int num_rows = 4000 / (CUBESIZE); 
    int num_cols = 4000 / (CUBESIZE);
    bool board[num_rows][num_cols];
    bool pause = true;
    int counter = 0;
    int colour_choice = 0;
    Color draw_colour = WHITE;

    srand((unsigned) time(NULL));

    InitWindow(screenWidth, screenHeight, "The Game of Life");

    SetTargetFPS(120);               // Set our game to run at 120 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Vector2 mouse = GetMousePosition();
        if (IsKeyPressed(KEY_R)) ranzomise_board(num_rows, num_cols, board);
        if (IsKeyPressed(KEY_B)) clear_board(num_rows, num_cols, board);
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
        
        check_fullscreen();

        // check for user mouse input
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            board[((int)mouse.x) / CUBESIZE][((int)mouse.y) / CUBESIZE] = 1;
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
            // mouse position debug log
            //DrawText(TextFormat("Mouse position: [%i , %i]", (int)mouse.x, (int)mouse.y), 350, 25, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}


//------------------------------------------------------------------------------------
// Function definitions 
//------------------------------------------------------------------------------------
void ranzomise_board(int num_rows, int num_cols, bool board[num_rows][num_cols]) {
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

void clear_board(int num_rows, int num_cols, bool board[num_rows][num_cols]) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            board[i][j] = 0;
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

void check_fullscreen(void) {
    // check for alt + enter
    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
        // see what display we are on right now
        int display = GetCurrentMonitor();
        if (IsWindowFullscreen()) {
            // if we are full screen, then go back to the windowed size
            SetWindowSize(screenWidth, screenHeight);
        }
        else {
            // if we are not full screen, set the window size to match the monitor we are on
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }
        ToggleFullscreen();
    }
}
