#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BLANK ' '

void initialise_random(int num_rows, int num_cols, char board[num_rows][num_cols], char input);
void print_board(int num_rows, int num_cols, char board[num_rows][num_cols]);
void game_step(int num_rows, int num_cols, char board[num_rows][num_cols], char key);

int main(int argv, char **argc) {

    srand((unsigned) time(NULL));
    int num_rows, num_cols, speed;

    switch (argv) {
        case 1: printf("Usage: ./main rows cols [speed]\n"); exit(EXIT_FAILURE);
        case 2: num_rows = atoi(argc[1]); num_cols = atoi(argc[1]); speed = 3; break;
        case 3: num_rows = atoi(argc[1]); num_cols = atoi(argc[2]); speed = 3; break;
        case 4: num_rows = atoi(argc[1]); num_cols = atoi(argc[2]); speed = atoi(argc[3]); break;
        default: printf("ERROR: Too many arguments\n"); exit(EXIT_FAILURE);
    }
    
    char board[num_rows][num_cols];
    initialise_random(num_rows, num_cols, board, 'o');
    print_board(num_rows, num_cols, board);
    for (;;) {
        system("clear");
        game_step(num_rows, num_cols, board, 'o');
        print_board(num_rows, num_cols, board);
        usleep(speed * 10000);
    }
}

void initialise_random(int num_rows, int num_cols, char board[num_rows][num_cols], char input) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if ((rand() % 5) == 0) {
                board[i][j] = input; 
            } else {
                board[i][j] = BLANK;
            }
        }
    }
}

void print_board(int num_rows, int num_cols, char board[num_rows][num_cols]) {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
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
                case 0: board[i][j] = BLANK; break;
                case 1: board[i][j] = BLANK; break;
                case 2: if (board[i][j] == key) board[i][j] = key; break;
                case 3: board[i][j] = key; break;
                case 4: board[i][j] = BLANK; break;
                case 5: board[i][j] = BLANK; break;
                case 6: board[i][j] = BLANK; break;
                case 7: board[i][j] = BLANK; break;
                case 8: board[i][j] = BLANK; break;
            }
        }
    }
}
