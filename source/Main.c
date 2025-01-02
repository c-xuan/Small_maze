#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAX_ROWS 50
#define MAX_COLS 50

// ��������
int high_score[3] = { 0,0,0 };
char chg;
// �w�q��V
int dx[] = { -2, 2, 0, 0 };
int dy[] = { 0, 0, -2, 2 };

// �H�����ä�V
void shuffle_directions(int directions[4]) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = directions[i];
        directions[i] = directions[r];
        directions[r] = temp;
    }
}

// �`���u���j�M�ͦ��g�c
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

// �H���g�c�ͦ�
void generate_maze(char map[MAX_ROWS][MAX_COLS], int rows, int cols, int* startX, int* startY, int* goalX, int* goalY) {
    // ��l�ưg�c
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map[i][j] = '@';
        }
    }

    // �_�I�M���I
    *startX = 1; *startY = 1;
    *goalX = rows - 2; *goalY = cols - 2;
    map[*startX][*startY] = 'O';
    map[*goalX][*goalY] = 'X';

    // �}�l�ͦ��g�c
    map[*startX][*startY] = ' ';
    dfs_generate(map, *startX, *startY, rows, cols);

}

// �C������禡
void move(char map[MAX_ROWS][MAX_COLS], int rows, int cols, int x, int y, int p, int q, char chg) {
    int steps = 0;
    time_t start_time = time(NULL);

    // ��l�Ʀa�Ϩ���ܪ�l�e��
    system("cls");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            putchar(map[i][j]);
        }
        printf("\n");
    }
    // ��̰ܳ��� 
    if (chg == '1')
        if (high_score[0] == 1000)printf("�ثe�����G0\n");
        else printf("�ثe�����G%d\n", high_score[0]);
    else if (chg == '2')
        if (high_score[1] == 1000)printf("�ثe�����G0\n");
        else printf("�ثe�����G%d\n", high_score[1]);
    else if (chg == '3')
        if (high_score[2] == 1000)printf("�ثe�����G0\n");
        else printf("�ثe�����G%d\n", high_score[2]);

    // �]�m���Ц�m�]Windows �t�Ρ^
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    // ��l�ƪ��a���_�l��m
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(hConsole, coord);
    putchar('O');


    while (x != p || y != q) {
        // ���ݪ��a��J
        char ch = getch();

        // �P�_���ʬO�_�X�k�A��s�a��
        int new_x = x, new_y = y;
        if ((ch == 's' || ch == 'S') && map[x + 1][y] != '@') new_x++;
        else if ((ch == 'w' || ch == 'W') && map[x - 1][y] != '@') new_x--;
        else if ((ch == 'a' || ch == 'A') && map[x][y - 1] != '@') new_y--;
        else if ((ch == 'd' || ch == 'D') && map[x][y + 1] != '@') new_y++;

        // �p�G��m���ܤơA��s�a��
        if (new_x != x || new_y != y) {
            coord.X = y;
            coord.Y = x;
            SetConsoleCursorPosition(hConsole, coord);
            putchar(' ');  // �M���¦�m

            x = new_x;
            y = new_y;

            coord.X = y;
            coord.Y = x;
            SetConsoleCursorPosition(hConsole, coord);
            putchar('O');  // ��s�s��m

            steps++;

        }
    }

    // �p��C�������ɶ�
    time_t end_time = time(NULL);
    double time_diff = difftime(end_time, start_time);

    // ��ܹC�������T��
    system("cls");
    printf("�����C���I�`�@���ʤF %d �B�C\n", steps);
    printf("�A��F %.2f �����C���C\n", time_diff);

    // �p�����
    int total_score = 1000 - (steps + (int)time_diff);
    if (total_score < 0) {
        total_score = 0;
    }

    if (chg == '1')
    {
        if (total_score > high_score[0]) {
            high_score[0] = total_score;
            printf("�s�����I���ߨ�s�����I\n");
        }
        else {
            printf("����s�����A�[�o�I\n");
        }
    }
    if (chg == '2')
    {
        if (total_score < high_score[1]) {
            high_score[1] = total_score;
            printf("�s�����I���ߨ�s�����I\n");
        }
        else {
            printf("����s�����A�[�o�I\n");
        }
    }
    if (chg == '3')
    {
        if (total_score < high_score[2]) {
            high_score[2] = total_score;
            printf("�s�����I���ߨ�s�����I\n");
        }
        else {
            printf("����s�����A�[�o�I\n");
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
        printf("1. �H���g�c(²��)\n2. �H���g�c(����)\n3. �H���g�c(�x��)\n4. �d�ݰ���\n5. ����\n�п��(1~5)�G");
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
                if (high_score[0] == 1000)printf("�ثe�����G0\n");
                else printf("�ثe�����G%d\n", high_score[0]);

                if (high_score[1] == 1000)printf("�ثe�����G0\n");
                else printf("�ثe�����G%d\n", high_score[1]);

                if (high_score[2] == 1000)printf("�ثe�����G0\n");
                else printf("�ثe�����G%d\n", high_score[2]);
                system("pause");
                break;
            case 5:
                break;
            }
        }
        else {
            printf("�L�Ŀﶵ�A�Э��s��J�I\n");
            Sleep(500);
        }
    } while (chg != 5);

    printf("�����C���I\n");
    return 0;
}