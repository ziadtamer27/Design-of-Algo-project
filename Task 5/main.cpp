#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
int targetmotion(int targetPos, int n) {
    int dir = rand() % 2; // 0 = left, 1 = right
    if (targetPos == 1)
        return 2;
    if (targetPos == n)
        return n - 1;
    if (dir == 0)
        return targetPos - 1;
    else
        return targetPos + 1;
}
void forwardhit(int left, int right, vector<int>& shots) {// Divide & Conquer Increasing Traversal
    if (left > right)
        return;
    if (left == right) {
        shots.push_back(left);
        return;
    }
    int mid = (left + right) / 2;
    forwardhit(left, mid, shots);
    forwardhit(mid + 1, right, shots);
}
void backwardhit(int left, int right, vector<int>& shots) {// Divide & Conquer Decreasing Traversal
    if (left > right)
        return;
    if (left == right) {
        shots.push_back(left);
        return;
    }
    int mid = (left + right) / 2;
    backwardhit(mid + 1, right, shots);
    backwardhit(left, mid, shots);
}
vector<int> shootseq(int n) {//Shot Sequence
    vector<int> shots;
    if (n == 2) {
        shots.push_back(1);
        shots.push_back(1);
        return shots;
    }
    forwardhit(2, n - 1, shots);
    backwardhit(2, n - 1, shots);
    return shots;
}
void HITT(int n, vector<int>& shots) {
    int target = rand() % n + 1;
    cout << "initial target slot: " << target << endl;
    cout << endl;
    for (int i = 0; i < shots.size(); i++) {
        cout << "Shot " << i + 1
             << ": shoot at slot "
             << shots[i];
        if (shots[i] == target) {
            cout << endl << " * TARGET IS HIT * " << endl;
            return;
        }
        cout << " (Miss)" << endl;
        target = targetmotion(target, n);
        cout << "target moved to: "
             << target << endl << endl;
    }
}
int main() {
    srand(time(0));
    int n;
    cout << "enter number of slots: ";
    cin >> n;
    if (n <= 1) {
        cout << "error: n must be greater than 1" << endl;
        return 0;
    }
    vector<int> shots = shootseq(n);
    cout << "Shooting sequence: " ;
    for (int shot : shots)
        cout << shot << " ";
    cout << "\n";
    HITT(n, shots);
    return 0;
}
