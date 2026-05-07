#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> Point;            //(row, col)
typedef vector<Point> Line;             //vector of points represent a line
typedef vector<vector<Point>> Grid;     // 2D grid of points
unordered_map<string, Line> dp_memo;    //maps (r,c,direction,length) -> the line segment already computed


// extend a line from (r,c) in direction dir for 'steps' steps
// dir: 0=right, 1=down, 2=left, 3=up
Line dp_createSegment(int r, int c, int dir, int steps, const Grid& grid, int n) {
    string key = to_string(r) + "," + to_string(c) + "," + to_string(dir) + "," + to_string(steps);
    if (dp_memo.count(key)) return dp_memo[key];    //to avoid recomputing the same segment again and again
    Line seg;
    seg.push_back(grid[r][c]);

    int dr[] = { 0,  1,  0, -1 };   // direction of movement vertically
    int dc[] = { 1,  0, -1,  0 };   // direction of movement horizontally

    int cr = r, cc = c; // current position
    for (int i = 0; i < steps; ++i) {
        cr += dr[dir];
        cc += dc[dir];
        if (cr < 0 || cr >= n || cc < 0 || cc >= n) break;
        seg.push_back(grid[cr][cc]);
    }
    dp_memo[key] = seg; //for memoisation
    return seg;
}

void findPath(int n, vector<Line>& Lines) {
    Grid grid(n, vector<Point>(n));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            grid[r][c] = {r, c};

    cout << "Grid (" << n << " x " << n << "):\n";
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c)
            cout << "(" << grid[r][c].first << "," << grid[r][c].second << ") ";
        cout << "\n";
    }

    int mid = (n % 2 == 0) ? n / 2 - 1 : n / 2;

    // ── First four lines (same for all n)
    // Line 1
        Line l1;
        l1.push_back(grid[mid+1][mid-1]);
        l1.push_back(grid[mid][mid]);
        l1.push_back(grid[mid-1][mid+1]);
        Lines.push_back(l1);

    // Line 2
        Line l2;
        l2.push_back(grid[mid-1][mid+1]);
        l2.push_back(grid[mid  ][mid+1]);
        l2.push_back(grid[mid+1][mid+1]);
        if (mid + 2 < n) l2.push_back(grid[mid+2][mid+1]);
        Lines.push_back(l2);

    // Line 3
        Line l3;
        if (mid + 2 < n) l3.push_back(grid[mid+2][mid+1]);
        l3.push_back(grid[mid+1][mid  ]);
        l3.push_back(grid[mid  ][mid-1]);
        if (mid - 2 >= 0) l3.push_back(grid[mid-1][mid-2]);
        Lines.push_back(l3);

    // Line 4
        Line l4;
        if (mid - 2 >= 0) l4.push_back(grid[mid-1][mid-2]);
        l4.push_back(grid[mid-1][mid-1]);
        l4.push_back(grid[mid-1][mid  ]);
        l4.push_back(grid[mid-1][mid+1]);
        if (mid + 2 < n) l4.push_back(grid[mid-1][mid+2]);
        Lines.push_back(l4);

    //if n = 4: two extra lines are added
    if (n == 4) {
        int r = mid - 1, c = mid + 2;
        Line l5 = dp_createSegment(r, c, 1, 3, grid, n);
        Lines.push_back(l5);
        r = mid + 2; 

        Line l6 = dp_createSegment(r, c, 2, 3, grid, n);
        Lines.push_back(l6);
        return;
    }

    // n > 4: spiral outward
    if (n > 4) {
        // Line 5:
        int r = mid - 1, c = mid + 2;
        Line l5 = dp_createSegment(r, c, 1, 3, grid, n);
        Lines.push_back(l5);
        
        r   = mid + 2;
        c   = mid + 2;
        int x   = 4;       
        int dir = 2;       // dir: 0=right, 1=down, 2=left, 3=up
        while (x < n - 1) {
            Line seg = dp_createSegment(r, c, dir, x, grid, n);
            Lines.push_back(seg);

            int dr[] = { 0,  1,  0, -1 }; 
            int dc[] = { 1,  0, -1,  0 };   
            
            r += dr[dir] * x;
            c += dc[dir] * x;

            if (dir == 1 || dir == 3) x++;   
            dir = (dir + 1) % 4;
        }
        //closing spiral
        if (x == n - 1) {
            if (n % 2 != 0) {           // Odd n: left, up, right
                int grid_dirs[] = {2, 3, 0}; 
                int steps = x;
                for (int d : grid_dirs) {
                    Line seg = dp_createSegment(r, c, d, steps, grid, n);
                    Lines.push_back(seg);
                    int dr2[] = {0, 1, 0, -1};
                    int dc2[] = {1, 0, -1, 0};
                    r += dr2[d] * steps;
                    c += dc2[d] * steps;
                }
            } 
            else {          // Even n: right, down, left
                int grid_dirs[] = {0, 1, 2};
                int steps = x;
                for (int d : grid_dirs) {
                    Line seg = dp_createSegment(r, c, d, steps, grid, n);
                    Lines.push_back(seg);
                    int dr2[] = {0, 1, 0, -1};
                    int dc2[] = {1, 0, -1, 0};
                    r += dr2[d] * steps;
                    c += dc2[d] * steps;
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the order of the dots (n > 2): ";
    cin >> n;

    if (n <= 2) {
        cout << "Error: n must be greater than 2.\n";
        return 1;
    }
    vector<Line> Lines;
    findPath(n, Lines);

    cout << "\n=====================================================\n"; ;
    for (int i = 0; i < Lines.size(); ++i) {
        cout << "Line " << i + 1 << ": ";
        for (int j = 0; j < Lines[i].size(); ++j) {
            cout << "(" << Lines[i][j].first << "," << Lines[i][j].second << ")";
            if (j + 1 < Lines[i].size()) cout << " -> ";
        }
        cout << "\n";
    }
    cout << "\nTotal number of lines : " << Lines.size() << "\n";
    cout << "Expected (2n - 2)     : " << (2 * n - 2) << "\n";
    return 0;
}
