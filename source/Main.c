#include <stdio.h>

// 定義迷宮的大小
#define ROWS 5
#define COLS 5

// 定義迷宮結構
int maze[ROWS][COLS] = {
    {1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 0, 1},
    {0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1}
};

// 定義玩家初始位置
int playerX = 0, playerY = 0;

// 定義終點位置
int goalX = 4, goalY = 4;

// 顯示迷宮
void printMaze(int playerX, int playerY) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == playerX && j == playerY)
                printf("P "); // 玩家位置
            else if (i == goalX && j == goalY)
                printf("G "); // 終點位置
            else if (maze[i][j] == 0)
                printf("█ "); // 障礙物
            else
                printf(". "); // 可通行路徑
        }
        printf("\n");
    }
}

// 判斷是否可以移動
int isValidMove(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 1;
}

int main() {
    printf("歡迎來到迷宮遊戲！使用 W/A/S/D 移動玩家到達終點 (G)。\n");

    while (1) {
        printMaze(playerX, playerY);

        // 玩家輸入
        printf("請輸入移動指令 (W=上, A=左, S=下, D=右): ");
        char move;
        scanf(" %c", &move);

        // 計算新位置
        int newX = playerX, newY = playerY;
        if (move == 'W' || move == 'w') newX--;
        else if (move == 'S' || move == 's') newX++;
        else if (move == 'A' || move == 'a') newY--;
        else if (move == 'D' || move == 'd') newY++;

        // 檢查移動是否合法
        if (isValidMove(newX, newY)) {
            playerX = newX;
            playerY = newY;
        }
        else {
            printf("無法移動到該位置！請重新輸入。\n");
        }

        // 檢查是否到達終點
        if (playerX == goalX && playerY == goalY) {
            printf("恭喜你到達終點！遊戲結束！\n");
            break;
        }
    }

    return 0;
}