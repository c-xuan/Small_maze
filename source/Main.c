#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h> // 引入時間相關庫

// 遊戲執行函式
void move(char map[40][40], int rows, int cols, int x, int y, int p, int q) {

    int steps = 0; // 步數統計

    // 記錄開始時間
    time_t start_time = time(NULL); // 獲取當前時間

    while (x != p || y != q) {
        system("cls"); // 清除畫面

        // 列印地圖
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                putchar(map[i][j]); // 逐字輸出
            }
            printf("\n"); // 換行
        }

        char ch = getch(); // 獲取玩家輸入
        if ((ch == 's' || ch == 'S') && map[x + 1][y] != '#') { // 下
            map[x][y] = ' ';
            x++;
            steps++; // 計步
            map[x][y] = 'O';
        }
        if ((ch == 'w' || ch == 'W') && map[x - 1][y] != '#') { // 上
            map[x][y] = ' ';
            x--;
            steps++; // 計步
            map[x][y] = 'O';
        }
        if ((ch == 'a' || ch == 'A') && map[x][y - 1] != '#') { // 左
            map[x][y] = ' ';
            y--;
            steps++; // 計步
            map[x][y] = 'O';
        }
        if ((ch == 'd' || ch == 'D') && map[x][y + 1] != '#') { // 右
            map[x][y] = ' ';
            y++;
            steps++; // 計步
            map[x][y] = 'O';
        }
    }

    // 記錄結束時間
    time_t end_time = time(NULL); // 獲取當前時間
    // 計算玩家完成所需時間
    double time_diff = difftime(end_time, start_time);

    // 遊戲完成訊息
    system("cls");
    printf("完成遊戲！總共移動了 %d 步。\n", steps);
    printf("你花了 %.2f 秒完成遊戲。\n", time_diff);
    system("pause");
}

int main() {

    int chg;
    do {
        system("cls");
        printf("1. 簡單\n2. 中等\n3. 困難\n4. 結束\n請選擇地圖：");
        scanf("%d", &chg);

        // 遊戲選擇
        switch (chg) {
        case 1: {
            char map[40][40] = {
                "##########",
                "#O    #  #",
                "#  #     #",
                "#  #  ## #",
                "#    ##X #",
                "##########"
            };
            int rows = 6, cols = 10, startX = 1, startY = 1, goalX = 4, goalY = 7;
            move(map, rows, cols, startX, startY, goalX, goalY);
            break;
        }
        case 2: {
            char map[40][40] = {
                "####################",
                "#O       #         #",
                "########  #  ### ###",
                "#             ##   #",
                "### ####  ##  ##   #",
                "#     ##  #        #",
                "# ### ##  # ########",
                "# ##        #      #",
                "# X  ####   ####  ##",
                "####################"
            };
            int rows = 10, cols = 20, startX = 1, startY = 1, goalX = 8, goalY = 2;
            move(map, rows, cols, startX, startY, goalX, goalY);
            break;
        }
        case 3: {
            char map[40][40] = {
                "##############################",
                "#O   #       ##       ##     #",
                "###  ######  ##  #######  ####",
                "#    #    #      ##         ##",
                "####    ###  ##  ##  #########",
                "#    ##  ##  ##      ##      #",
                "###  ##      ###########  ####",
                "#    ##  ##          ##      #",
                "######  ##  ########  ##  ####",
                "#        ##  ##       ##     #",
                "###  ######  ##  ### #########",
                "#    #       ##  ##          #",
                "#  #####  ##     ##  # #######",
                "#      #  ##  ########     X #",
                "##############################"
            };
            int rows = 15, cols = 30, startX = 1, startY = 1, goalX = 13, goalY = 27;
            move(map, rows, cols, startX, startY, goalX, goalY);
            break;
        }
        case 4:
            system("cls");
            printf("結束遊戲！\n");
            break;
        default:
            printf("無效選項，請重新選擇！\n");
            break;
        }
    } while (chg != 4);

    return 0;
}
