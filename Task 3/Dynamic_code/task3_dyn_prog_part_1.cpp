#include <iostream>
#include <climits>
using namespace std;

long long dp[9];    // stores min moves for each n
int split_t[9];     // stores best split t for each n

void compute_dp(int n) {
    // base cases
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = LLONG_MAX;  // start with a large number

        // try every split point t
        for (int t = 1; t < i; t++) {
            // cost = move t disks twice + move rest with 3 pegs
            long long moves = 2LL * dp[t] + ((1LL << (i - t)) - 1);

            // keep the best (smallest) result
            if (moves < dp[i]) {
                dp[i] = moves;
                split_t[i] = t;   // save which t was best
            }
        }
    }
}

// classic 3-peg Hanoi
void move3(int n, char src, char dst, char aux) {
    if (n == 0) return;
    move3(n - 1, src, aux, dst);
    cout << "  Move disk " << n << ": " << src << " -> " << dst << "\n";
    move3(n - 1, aux, dst, src);
}

// 4-peg solver using the DP split table
void solve4(int n, char src, char dst, char a1, char a2) {
    if (n == 0) return;

    // single disk: just move it
    if (n == 1) {
        cout << "  Move disk 1: " << src << " -> " << dst << "\n";
        return;
    }

    int t = split_t[n];  // use the best split we found

    // step 1: move top t disks to buffer
    solve4(t, src, a1, dst, a2);

    // step 2: move remaining disks with 3 pegs
    move3(n - t, src, dst, a2);

    // step 3: move buffer disks to destination
    solve4(t, a1, dst, src, a2);
}

int main() {
    compute_dp(8);
    cout << "Minimum moves for 8 disks (4 pegs): " << dp[8] << "\n";
    cout << "\n--- Move sequence ---\n";
    solve4(8, 'A', 'D', 'B', 'C');
    return 0;
}