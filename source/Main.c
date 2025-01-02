#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX_ROWS 50
#define MAX_COLS 50

int dx[] = { -2, 2, 0, 0 };
int dy[] = { 0, 0, -2, 2 };

// Function to shuffle directions
void shuffle_directions(int directions[4]) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[r];
        directions[r] = temp;
    }
}

// Function to set cursor position
void set_cursor_position(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, coord);
}

// Recursive DFS to generate the maze
void dfs_generate(char map[MAX_ROWS][MAX_COLS], int x, int y, int rows, int cols) {
    int directions[4] = { 0, 1, 2, 3 };
    shuffle_directions(directions);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[directions[i]];
        int ny = y + dy[directions[i]];
        int wall_x = x + dx[directions[i]] / 2;
        int wall_y = y + dy[directions[i]] / 2;

        if (nx > 0 && nx < rows - 1 && ny > 0 && ny < cols - 1 && map[nx][ny] == '#') {
            map[wall_x][wall_y] = ' ';
            map[nx][ny] = ' ';
            // set_cursor_position(0, 0);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    putchar(map[i][j]);
                }
                printf("\n");
            }
            Sleep(50); // Control animation speed
            dfs_generate(map, nx, ny, rows, cols);
        }
    }
}

// Function to initialize and generate the maze
void generate_maze(char map[MAX_ROWS][MAX_COLS], int rows, int cols, int* startX, int* startY, int* goalX, int* goalY) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = '#';
        }
    }

    *startX = 1; *startY = 1;
    *goalX = rows - 2; *goalY = cols - 2;
    map[*startX][*startY] = 'O';
    map[*goalX][*goalY] = 'X';

    map[*startX][*startY] = ' ';
    dfs_generate(map, *startX, *startY, rows, cols);
}

int main() {
    srand(time(NULL));

    char map[MAX_ROWS][MAX_COLS];
    int rows = 25, cols = 50;
    int startX, startY, goalX, goalY;

    generate_maze(map, rows, cols, &startX, &startY, &goalX, &goalY);

    //set_cursor_position(0, rows + 1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            putchar(map[i][j]);
        }
        printf("\n");
    }

    return 0;
}
