#include <iostream>
using namespace std;

#define N 8
#define FREE -1
#define NOT_FREE 1
int row[N], col[N], dpos[2 * N - 1], dneg[2 * N - 1];
bool board[N][N];

void init() {
    for (int i = 0; i < N; i++) {
        row[i] = col[i] = FREE;
    }
    for (int i = 0; i < 2 * N - 1; i++) {
        dpos[i] = dneg[i] = FREE;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = false;
        }
    }
}

void printBoard() {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cout << (board[r][c] ? "Q" : ".");
        }
        cout << endl;
    }
}

void attack(int r, int c) {
    row[r] = col[c] = dpos[r + c] = dneg[r - c + N - 1] = NOT_FREE;
    board[r][c] = true;
}

void unattack(int r, int c) {
    row[r] = col[c] = dpos[r + c] = dneg[r - c + N - 1] = FREE;
    board[r][c] = false;
}

void recursive(int i) {
    if (i == N) {
        printBoard();
        return;
    }

    // すでにその行にクイーンがある場合はスキップ
    if (row[i] != FREE) {
        recursive(i + 1);
        return;
    }

    for (int j = 0; j<N; j++ ) {
        if (col[j] == FREE && dpos[i + j] == FREE && dneg[i - j + N - 1] == FREE) {
            attack(i, j);
            recursive(i + 1);
            unattack(i, j);
        }
    }
}

int main() {
    init();
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        attack(r, c);
    }

    recursive(0);

    return 0;
}
