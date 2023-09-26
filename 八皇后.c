#include <stdio.h>
#include <stdbool.h>
#define N 4

int board[N][N];
int solutionCount = 0;
int solutionCountKing = 0;

// 检查在row行和col列放置皇后是否合法
int isSafeQueen(int row, int col) {
    int i, j;

    // 检查列是否有皇后冲突
    for (i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return 0;
        }
    }

    // 检查左上对角线是否有皇后冲突
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return 0;
        }
    }

    // 检查右上对角线是否有皇后冲突
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) {
            return 0;
        }
    }

    return 1;
}

bool isSafe(int row, int col) {
    // 检查左上方是否有其他国王
    if (row > 0 && col > 0 && board[row - 1][col - 1] == 1) {
        return false;
    }

    // 检查上方是否有其他国王
    if (row > 0 && board[row - 1][col] == 1) {
        return false;
    }

    // 检查右上方是否有其他国王
    if (row > 0 && col < 3 && board[row - 1][col + 1] == 1) {
        return false;
    }

    // 检查左边是否有其他国王
    if (col > 0 && board[row][col - 1] == 1) {
        return false;
    }

    return true;
}


// 解决八皇后问题的递归函数
void solveNQueens(int row) {
    if (row >= N) {
        // 打印解决方案
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        solutionCount++;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafeQueen(row, i)) {
            board[row][i] = 1;
            solveNQueens(row + 1);
            board[row][i] = 0; // 回溯
        }
    }
}

void solveNKings(int row) {
    if (row >= N) {
        // 打印解决方案
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        solutionCountKing++;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(row, i)) {
            board[row][i] = 1;
            solveNKings(row + 1);
            board[row][i] = 0; // 回溯
        }
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    //solveNQueens(0);
    solveNKings(0);

    //printf("totally %d methods of 8 Queens\n", solutionCount);
    printf("totally %d methods of 4 kings\n", solutionCountKing);

    return 0;
}
