#include <bits/stdc++.h>
using namespace std;

int board[128][128];
int id = 1;

void tile(int x, int y, int row, int col, int size) {
    if (size == 2) {
        for (int i = x; i < x + 2; i++) {
            for (int j = y; j < y + 2; j++) {
                if (i != row || j != col) {
                    board[i][j] = id;
                }
            }
        }
        id++;
        return;
    }

    int mid = size / 2;
    int centerX = x + mid;
    int centerY = y + mid;

    int quad;

    if (row < centerX && col < centerY) quad = 1;
    else if (row < centerX && col >= centerY) quad = 2;
    else if (row >= centerX && col < centerY) quad = 3;
    else quad = 4;

    if (quad != 1) board[centerX - 1][centerY - 1] = id;
    if (quad != 2) board[centerX - 1][centerY] = id;
    if (quad != 3) board[centerX][centerY - 1] = id;
    if (quad != 4) board[centerX][centerY] = id;
    id++;

    if (quad == 1)
        tile(x, y, row, col, mid);
    else
        tile(x, y, centerX - 1, centerY - 1, mid);

    if (quad == 2)
        tile(x, centerY, row, col, mid);
    else
        tile(x, centerY, centerX - 1, centerY, mid);

    if (quad == 3)
        tile(centerX, y, row, col, mid);
    else
        tile(centerX, y, centerX, centerY - 1, mid);

    if (quad == 4)
        tile(centerX, centerY, row, col, mid);
    else
        tile(centerX, centerY, centerX, centerY, mid);
}

int main() {
    int n;
    cin >> n;
    int row, col;
    cin >> row >> col;
    
    int size = pow(2,n);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = 0;

    tile(0, 0, row, col, size);

    board[row][col] = -1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}
