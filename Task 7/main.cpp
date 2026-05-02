#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bruteForce(vector<int> t, vector<int> d, vector<int> p) {
    int n = t.size();

    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i;

    int ans = 1e9;

    do {
        int time = 0, penalty = 0;

        for (int i = 0; i < n; i++) {
            int j = perm[i];
            time += t[j];

            if (time > d[j])
                penalty += p[j];
        }

        ans = min(ans, penalty);

    } while (next_permutation(perm.begin(), perm.end()));

    return ans;
}


int dpSolution(vector<int> t, vector<int> d, vector<int> p) {
    int n = t.size();

    // sort by deadline
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return d[a] < d[b];
    });

    int maxD = 0;
    for (int i = 0; i < n; i++)
        maxD = max(maxD, d[i]);

    vector<int> dp(maxD + 1, 0);

    for (int k = 0; k < n; k++) {
        int j = idx[k];

        for (int time = d[j]; time >= t[j]; time--) {
            dp[time] = max(dp[time], dp[time - t[j]] + p[j]);
        }
    }

    int total = 0;
    for (int i = 0; i < n; i++)
        total += p[i];

    int best = 0;
    for (int i = 0; i <= maxD; i++)
        best = max(best, dp[i]);

    return total - best;
}


void solve(vector<int>& t, vector<int>& d, vector<int>& p, vector<bool>& used,int time, int penalty, int& ans) {

    int n = t.size();
    
    // if all jobs considered
    bool done = true;

    if (penalty >= ans) return;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            done = false;
            break;
        }
    }

    if (done) {
        ans = min(ans, penalty);
        return;
    }

    // try each unused job
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;

            int newTime = time + t[i];
            int newPenalty = penalty;

            if (newTime > d[i])
                newPenalty += p[i];

            solve(t, d, p, used, newTime, newPenalty, ans);

            used[i] = false; // backtrack
        }
    }
}

int divideConquer(vector<int> t, vector<int> d, vector<int> p) {
    int n = t.size();
    vector<bool> used(n, false);

    int ans = 1e9;

    solve(t, d, p, used, 0, 0, ans);

    return ans;
}

int main() {
vector<int> t = {1, 3, 2, 1};
vector<int> d = {2, 3, 3, 1};
vector<int> p = {20, 50, 30, 10};

    cout << "Brute Force = " << bruteForce(t, d, p) << endl;
    cout << "Divide & Conquer = " << divideConquer(t, d, p) << endl;
    cout << "DP = " << dpSolution(t, d, p) << endl;

    return 0;
}