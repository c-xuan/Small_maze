#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAX_ROWS 50
#define MAX_COLS 50

// 高分紀錄
int high_score[3] = { 0,0,0 };
char chg;
// 定義方向
int dx[] = { -2, 2, 0, 0 };
int dy[] = { 0, 0, -2, 2 };

// 隨機打亂方向
void shuffle_directions(int directions[4]) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[r];
        directions[r] = temp;
    }
}

// 深度優先搜尋生成迷宮
void dfs_generate(char map[MAX_ROWS][MAX_COLS], int x, int y, int rows, int cols) {
    int directions[4] = { 0, 1, 2, 3 };
    shuffle_directions(directions);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[directions[i]];
        int ny = y + dy[directions[i]];
        int wall_x = x + dx[directions[i]] / 2;
        int wall_y = y + dy[directions[i]] / 2;

        if (nx > 0 && nx < rows - 1 && ny > 0 && ny < cols - 1 && map[nx][ny] == '@') {
            map[wall_x][wall_y] = ' ';
            map[nx][ny] = ' ';
            dfs_generate(map, nx, ny, rows, cols);
        }
    }
}

// 隨機迷宮生成
void generate_maze(char map[MAX_ROWS][MAX_COLS], int rows, int cols, int* startX, int* startY, int* goalX, int* goalY) {
    // 初始化迷宮
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = '@';
        }
    }

    // 起點和終點
    *startX = 1; *startY = 1;
    *goalX = rows - 2; *goalY = cols - 2;
    map[*startX][*startY] = 'O';
    map[*goalX][*goalY] = 'X';

    // 開始生成迷宮
    map[*startX][*startY] = ' ';
    dfs_generate(map, *startX, *startY, rows, cols);

}

// 遊戲執行函式
void move(char map[MAX_ROWS][MAX_COLS], int rows, int cols, int x, int y, int p, int q, char chg) {
    int steps = 0;
    time_t start_time = time(NULL);

    // 初始化地圖並顯示初始畫面
    system("cls");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            putchar(map[i][j]);
        }
        printf("\n");
    }
    // 顯示最高分 
    if (chg == '1')
        if (high_score[0] == 1000)printf("目前高分：0\n");
        else printf("目前高分：%d\n", high_score[0]);
    else if (chg == '2')
        if (high_score[1] == 1000)printf("目前高分：0\n");
        else printf("目前高分：%d\n", high_score[1]);
    else if (chg == '3')
        if (high_score[2] == 1000)printf("目前高分：0\n");
        else printf("目前高分：%d\n", high_score[2]);

    // 設置光標位置（Windows 系統）
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    // 初始化玩家的起始位置
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(hConsole, coord);
    putchar('O');


    while (x != p || y != q) {
        // 等待玩家輸入
        char ch = getch();

        // 判斷移動是否合法，更新地圖
        int new_x = x, new_y = y;
        if ((ch == 's' || ch == 'S') && map[x + 1][y] != '@') new_x++;
        else if ((ch == 'w' || ch == 'W') && map[x - 1][y] != '@') new_x--;
        else if ((ch == 'a' || ch == 'A') && map[x][y - 1] != '@') new_y--;
        else if ((ch == 'd' || ch == 'D') && map[x][y + 1] != '@') new_y++;

        // 如果位置有變化，更新地圖
        if (new_x != x || new_y != y) {
            coord.X = y;
            coord.Y = x;
            SetConsoleCursorPosition(hConsole, coord);
            putchar(' ');  // 清除舊位置

            x = new_x;
            y = new_y;

            coord.X = y;
            coord.Y = x;
            SetConsoleCursorPosition(hConsole, coord);
            putchar('O');  // 更新新位置

            steps++;

        }
    }

    // 計算遊戲完成時間
    time_t end_time = time(NULL);
    double time_diff = difftime(end_time, start_time);

    // 顯示遊戲完成訊息
    system("cls");
    printf("完成遊戲！總共移動了 %d 步。\n", steps);
    printf("你花了 %.2f 秒完成遊戲。\n", time_diff);

    // 計算分數
    int total_score = 1000 - (steps + (int)time_diff);
    if (total_score < 0) {
        total_score = 0;
    }

    if (chg == '1')
    {
        if (total_score > high_score[0]) {
            high_score[0] = total_score;
            printf("新高分！恭喜刷新紀錄！\n");
        }
        else {
            printf("未刷新高分，加油！\n");
        }
    }
    if (chg == '2')
    {
        if (total_score < high_score[1]) {
            high_score[1] = total_score;
            printf("新高分！恭喜刷新紀錄！\n");
        }
        else {
            printf("未刷新高分，加油！\n");
        }
    }
    if (chg == '3')
    {
        if (total_score < high_score[2]) {
            high_score[2] = total_score;
            printf("新高分！恭喜刷新紀錄！\n");
        }
        else {
            printf("未刷新高分，加油！\n");
        }
    }
    Sleep(500);
    system("pause");
}

void play_game(int rows, int cols, char chg) {
    char map[MAX_ROWS][MAX_COLS];
    int startX, startY, goalX, goalY;
    generate_maze(map, rows, cols, &startX, &startY, &goalX, &goalY);
    move(map, rows, cols, startX, startY, goalX, goalY, chg);
}

int main() {
    srand(time(NULL));


    do {
        system("cls");
        printf("1. 隨機迷宮(簡單)\n2. 隨機迷宮(中等)\n3. 隨機迷宮(困難)\n4. 查看高分\n5. 結束\n請選擇(1~5)：");
        scanf("%d", &chg);
        if (chg >= 1 && chg <= 5) {
            switch (chg) {
            case 1:
                play_game(5, 10, '1');
                break;
            case 2:
                play_game(15, 30, '2');
                break;
            case 3:
                play_game(25, 50, '3');
                break;
            case 4:
                system("cls");
                if (high_score[0] == 1000)printf("目前高分：0\n");
                else printf("目前高分：%d\n", high_score[0]);

                if (high_score[1] == 1000)printf("目前高分：0\n");
                else printf("目前高分：%d\n", high_score[1]);

                if (high_score[2] == 1000)printf("目前高分：0\n");
                else printf("目前高分：%d\n", high_score[2]);
                system("pause");
                break;
            case 5:
                break;
            }
        }
        else {
            printf("無效選項，請重新輸入！\n");
            Sleep(500);
        }
    } while (chg != 5);

    printf("結束遊戲！\n");
    return 0;
}