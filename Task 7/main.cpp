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


int divideConquer(vector<int>& t,vector<int>& d,vector<int>& p,vector<bool>& used,int time,int penalty) {

    int n = t.size();

    bool done = true;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            done = false;
            break;
        }
    }

    if (done)
        return penalty;

    int ans = 1e9;

    for (int i = 0; i < n; i++) {

        if (!used[i]) {

            used[i] = true;

            int newTime = time + t[i];
            int newPenalty = penalty;

            if (newTime > d[i])
                newPenalty += p[i];

            ans = min(ans, divideConquer(t, d, p, used, newTime, newPenalty));

            used[i] = false;
        }
    }

    return ans;
}

int main() {
    vector<int> t = {1, 2, 3};
    vector<int> d = {3, 3, 3};
    vector<int> p = {10, 20, 30};


    int n = t.size();
    vector<bool> used(n, false);

    cout << "Brute Force = " << bruteForce(t, d, p) << endl;

    cout << "Divide & Conquer = "<< divideConquer(t, d, p, used, 0, 0) << endl;

    cout << "DP = " << dpSolution(t, d, p) << endl;

    return 0;
}