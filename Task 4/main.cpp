#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int ROWS = 4;
const int COLS = 3;

int dr[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
int dc[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };

struct Node {
    string board;
    vector<string> path;
};

void printBoard(string board) {
    for (int i = 0; i < board.size(); i++) {
        cout << board[i] << " ";

        if ((i + 1) % COLS == 0)
            cout << endl;
    }

    cout << "----------" << endl;
}

vector<string> getNextBoards(string board) {
    vector<string> nextBoards;

    for (int i = 0; i < board.size(); i++) {
        if (board[i] == '.')
            continue;

        int row = i / COLS;
        int col = i % COLS;

        for (int k = 0; k < 8; k++) {
            int newRow = row + dr[k];
            int newCol = col + dc[k];

            if (newRow >= 0 && newRow < ROWS &&
                newCol >= 0 && newCol < COLS) {

                int newIndex = newRow * COLS + newCol;

                if (board[newIndex] == '.') {
                    string newBoard = board;
                    swap(newBoard[i], newBoard[newIndex]);
                    nextBoards.push_back(newBoard);
                }
            }
        }
    }

    return nextBoards;
}

int main() {
    string start = "BBB......WWW";
    string goal  = "WWW......BBB";

    queue<Node> q;
    set<string> visited;

    q.push({start, {start}});
    visited.insert(start);

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.board == goal) {
            cout << "Minimum number of moves = "
                 << current.path.size() - 1 << endl << endl;

            for (int i = 0; i < current.path.size(); i++) {
                cout << "Step " << i << ":" << endl;
                printBoard(current.path[i]);
            }

            return 0;
        }

        vector<string> nextBoards = getNextBoards(current.board);

        for (string next : nextBoards) {
            if (visited.find(next) == visited.end()) {
                visited.insert(next);

                vector<string> newPath = current.path;
                newPath.push_back(next);

                q.push({next, newPath});
            }
        }
    }

    cout << "No solution found." << endl;

    return 0;
}
