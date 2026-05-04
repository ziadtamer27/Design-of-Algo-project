#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

typedef vector<double> Point;
vector<vector<Point>> dacClustering(vector<Point> P, int k);

int main() {
    cout << "====== DEVIDE AND CONQUER ======" << endl;
    int n, k;
    cout << "Enter the number of points and clusters: ";
    cin >> n >> k;

    vector<Point> P(n);
    cout << "Enter the points (each point as space-separated values):" << endl;
    for (int i = 0; i < n; ++i) {
        P[i].resize(2); // Assuming 2D points for simplicity
        cin >> P[i][0] >> P[i][1];
    }

    vector<vector<Point>> clusters = dacClustering(P, k);

    cout << "Clusters:" << endl;
    for (size_t i = 0; i < clusters.size(); ++i) {
        cout << "Cluster " << i << ":" << endl;
        for (const auto& point : clusters[i]) {
            cout << "(" << point[0] << ", " << point[1] << ")" << "  ";
        }
        cout << endl;
    }

    return 0;
}

vector<vector<Point>> dacClustering(vector<Point> P, int k) {
    if (P.size() == 1 || k == 1) {
        return { P }; // Base case: one cluster with all points
    }
    int d = P[0].size(), bestAxis = 0; // Dimension of points
    double maxSpread = -1;

    // Find the axis with the maximum spread
    for (int i = 0; i < d; ++i) {
        double minVal = numeric_limits<double>::max();
        double maxVal = numeric_limits<double>::lowest();
        for (const auto& point : P) {
            minVal = min(minVal, point[i]);
            maxVal = max(maxVal, point[i]);
        }
        double spread = maxVal - minVal;
        if (spread > maxSpread) {
            maxSpread = spread;
            bestAxis = i;
        }
    }

    // Split points based on the median of the best axis
    sort(P.begin(), P.end(), [bestAxis](const Point& a, const Point& b) {
        return a[bestAxis] < b[bestAxis];
        });
    int mid = P.size() / 2;
    vector<Point> left(P.begin(), P.begin() + mid);
    vector<Point> right(P.begin() + mid, P.end());

    // Proportional k allocation
    int kLeft = max(1, min(k - 1, (int)round((double)k * left.size() / P.size())));
    int kRight = k - kLeft;

    // Recursive and merge results
    auto leftClusters = dacClustering(left, kLeft);
    auto rightClusters = dacClustering(right, kRight);
    for (auto& cluster : rightClusters) {
        leftClusters.push_back(cluster);
    }
    return leftClusters;
}