#include <stdio.h>

// �w�q�g�c���j�p
#define ROWS 5
#define COLS 5

// �w�q�g�c���c
int maze[ROWS][COLS] = {
    {1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 1, 0, 1},
    {0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1}
};

// �w�q���a��l��m
int playerX = 0, playerY = 0;

// �w�q���I��m
int goalX = 4, goalY = 4;

// ��ܰg�c
void printMaze(int playerX, int playerY) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == playerX && j == playerY)
                printf("P "); // ���a��m
            else if (i == goalX && j == goalY)
                printf("G "); // ���I��m
            else if (maze[i][j] == 0)
                printf("�i "); // ��ê��
            else
                printf(". "); // �i�q����|
        }
        printf("\n");
    }
}

// �P�_�O�_�i�H����
int isValidMove(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 1;
}

int main() {
    printf("�w��Ө�g�c�C���I�ϥ� W/A/S/D ���ʪ��a��F���I (G)�C\n");

    while (1) {
        printMaze(playerX, playerY);

        // ���a��J
        printf("�п�J���ʫ��O (W=�W, A=��, S=�U, D=�k): ");
        char move;
        scanf(" %c", &move);

        // �p��s��m
        int newX = playerX, newY = playerY;
        if (move == 'W' || move == 'w') newX--;
        else if (move == 'S' || move == 's') newX++;
        else if (move == 'A' || move == 'a') newY--;
        else if (move == 'D' || move == 'd') newY++;

        // �ˬd���ʬO�_�X�k
        if (isValidMove(newX, newY)) {
            playerX = newX;
            playerY = newY;
        }
        else {
            printf("�L�k���ʨ�Ӧ�m�I�Э��s��J�C\n");
        }

        // �ˬd�O�_��F���I
        if (playerX == goalX && playerY == goalY) {
            printf("���ߧA��F���I�I�C�������I\n");
            break;
        }
    }

    return 0;
}