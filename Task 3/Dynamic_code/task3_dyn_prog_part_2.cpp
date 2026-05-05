#include <iostream>
#include <climits>
using namespace std;

long long dp_val[65];   // min moves for each n
int split_t[65];        // best split t for each n

void compute_dp(int maxN) {
    // base cases
    dp_val[0] = 0;
    dp_val[1] = 1;

    for (int i = 2; i <= maxN; i++) {
        dp_val[i] = LLONG_MAX;  // start with a large number

        // try every possible split point
        for (int t = 1; t < i; t++) {
            if (i - t > 62) continue;  // avoid integer overflow

            // cost = move t disks twice + move rest with 3 pegs
            long long mv = 2LL * dp_val[t] + ((1LL << (i - t)) - 1);

            // keep the smallest result
            if (mv < dp_val[i]) {
                dp_val[i] = mv;
                split_t[i] = t;  // remember best split
            }
        }
    }
}

// classic 3-peg Hanoi (no extra peg available)
void move3(int n, char s, char d, char a) {
    if (!n) return;
    move3(n - 1, s, a, d);
    cout << "  [3-peg] disk " << n << ": " << s << " -> " << d << "\n";
    move3(n - 1, a, d, s);
}

// 4-peg solver guided by the DP table
void solve4(int n, char s, char d, char a1, char a2) {
    if (!n) return;

    // single disk: move directly
    if (n == 1) {
        cout << "  disk 1: " << s << " -> " << d << "\n";
        return;
    }

    int t = split_t[n];  // best split for n disks

    // step 1: move top t disks to buffer using 4 pegs
    solve4(t, s, a1, d, a2);

    // step 2: move remaining disks using only 3 pegs
    move3(n - t, s, d, a2);

    // step 3: move buffer disks to destination using 4 pegs
    solve4(t, a1, d, s, a2);
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    // basic input check
    if (n < 1 || n > 62) {
        cout << "Please enter 1-62.\n";
        return 1;
    }

    compute_dp(n);
    cout << "Min moves for " << n << " disks (4 pegs): " << dp_val[n] << "\n";

    // only print moves for small n (avoids huge output)
    if (n <= 12) {
        cout << "\n--- Move sequence ---\n";
        solve4(n, 'A', 'D', 'B', 'C');
    }

    return 0;
}