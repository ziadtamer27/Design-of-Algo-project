#include <iostream>
using namespace std;

int n = 8;
int Chessboard[20][20];

int row_path[8] = {2,1,-1,-2,-2,-1,1,2};
int column_path[8] = {1,2,2,1,-1,-2,-2,-1};

int startX = 0, startY = 0;

bool isValid(int x, int y)
{
    if(x >= 0 && x < n && y >= 0 && y < n && Chessboard[x][y] == -1)
        return true;
    return false;
}
bool isClosedTour(int x, int y)
{
    for (int i = 0; i < 8; i++)
        if (x + row_path[i] == startX && y + column_path[i] == startY)
            return true;
    return false;
}

int countMoves(int x, int y)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + row_path[i];
        int ny = y + column_path[i];
        if (isValid(nx, ny))
            count++;
    }
    return count;
}

bool solve(int x, int y, int move)
{
    Chessboard[x][y] = move;

    if (move == n * n - 1)
        return isClosedTour(x, y);

    int bestX[8], bestY[8], deg[8];
    int count = 0;

    for (int i = 0; i < 8; i++)
    {
        int nx = x + row_path[i];
        int ny = y + column_path[i];

        if (isValid(nx, ny))
        {
            bestX[count] = nx;
            bestY[count] = ny;
            deg[count] = countMoves(nx, ny);
            count++;
        }
    }

    bool used[8] = {false};
    for (int k = 0; k < count; k++)
    {
        int minIdx = -1;
        int minDeg = 100;
        for (int i = 0; i < count; i++)
        {
            if (!used[i] && deg[i] < minDeg)
            {
                minDeg = deg[i];
                minIdx = i;
            }
        }

        if (minIdx == -1)
            break;

        used[minIdx] = true;
        int nx = bestX[minIdx];
        int ny = bestY[minIdx];

        if (solve(nx, ny, move + 1))
            return true;
    }

    Chessboard[x][y] = -1;
    return false;
}

int main()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Chessboard[i][j] = -1;

    if (solve(startX, startY, 0))
    {
        cout << "Closed Tour Found:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << Chessboard[i][j] << "\t";
            cout << endl;
        }
        cout << "Number of moves: " << n * n - 1 << endl;
    }
    else
    {
        cout << "No closed tour found";
    }
}
