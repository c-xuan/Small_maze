#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h> // �ޤJ�ɶ������w

// �C������禡
void move(char map[40][40], int rows, int cols, int x, int y, int p, int q) {

    int steps = 0; // �B�Ʋέp

    // �O���}�l�ɶ�
    time_t start_time = time(NULL); // �����e�ɶ�

    while (x != p || y != q) {
        system("cls"); // �M���e��

        // �C�L�a��
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                putchar(map[i][j]); // �v�r��X
            }
            printf("\n"); // ����
        }

        char ch = getch(); // ������a��J
        if ((ch == 's' || ch == 'S') && map[x + 1][y] != '#') { // �U
            map[x][y] = ' ';
            x++;
            steps++; // �p�B
            map[x][y] = 'O';
        }
        if ((ch == 'w' || ch == 'W') && map[x - 1][y] != '#') { // �W
            map[x][y] = ' ';
            x--;
            steps++; // �p�B
            map[x][y] = 'O';
        }
        if ((ch == 'a' || ch == 'A') && map[x][y - 1] != '#') { // ��
            map[x][y] = ' ';
            y--;
            steps++; // �p�B
            map[x][y] = 'O';
        }
        if ((ch == 'd' || ch == 'D') && map[x][y + 1] != '#') { // �k
            map[x][y] = ' ';
            y++;
            steps++; // �p�B
            map[x][y] = 'O';
        }
    }

    // �O�������ɶ�
    time_t end_time = time(NULL); // �����e�ɶ�
    // �p�⪱�a�����һݮɶ�
    double time_diff = difftime(end_time, start_time);

    // �C�������T��
    system("cls");
    printf("�����C���I�`�@���ʤF %d �B�C\n", steps);
    printf("�A��F %.2f �����C���C\n", time_diff);
    system("pause");
}

int main() {

    int chg;
    do {
        system("cls");
        printf("1. ²��\n2. ����\n3. �x��\n4. ����\n�п�ܦa�ϡG");
        scanf("%d", &chg);

        // �C�����
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
            printf("�����C���I\n");
            break;
        default:
            printf("�L�Ŀﶵ�A�Э��s��ܡI\n");
            break;
        }
    } while (chg != 4);

    return 0;
}
