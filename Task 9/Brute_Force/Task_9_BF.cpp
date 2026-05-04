#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

typedef vector<double> Point;
vector<int> bruteForceKMeans(const vector<Point>& P, int k);

int main() {
    cout << "====== BRUTE FORCE ======" << endl;
    int n, k;
    cout << "Enter the number of points and clusters: ";
    cin >> n >> k;

    vector<Point> P(n);
    cout << "Enter the points (each point as space-separated values):" << endl;
    for (int i = 0; i < n; ++i) {
        P[i].resize(2); // Assuming 2D points for simplicity
        cin >> P[i][0] >> P[i][1];
    }

    vector<int> assign = bruteForceKMeans(P, k);
    vector<vector<Point>> clusters(k);
    for (size_t i = 0; i < P.size(); ++i) {
        clusters[assign[i]].push_back(P[i]);
    }
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

double distance(const Point& a, const Point& b) {
    double dist = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        dist += pow(a[i] - b[i], 2);
    }
    return sqrt(dist);
}

Point calculateCentroid(const vector<Point>& cluster) {
    Point centroid(cluster[0].size(), 0.0);
    for (const auto& point : cluster) {
        for (int i = 0; i < point.size(); ++i) {
            centroid[i] += point[i];
        }
    }
    for (int i = 0; i < centroid.size(); ++i) {
        centroid[i] /= cluster.size();
    }
    return centroid;
}

double computeWCSS(const vector<Point>& cluster, const vector<int>& assign, int k) {
    vector<vector<Point>> clusters(k);
    for (size_t i = 0; i < cluster.size(); ++i) {
        clusters[assign[i]].push_back(cluster[i]);
    }
    double wcss = 0.0;
    for (int j = 0; j < k; j++) {
        if (clusters[j].empty()) return numeric_limits<double>::max(); // Invalid assignment, skip
        Point centroid = calculateCentroid(clusters[j]);
        for (const auto& point : clusters[j]) {
            double dist = distance(point, centroid);
            wcss += dist * dist; // Add squared distance to WCSS
        }
    }
    return wcss;
}

bool nextAssignment(vector<int>& curr, int k) {
    for (int i = curr.size() - 1; i >= 0; --i) {
        if (curr[i] < k - 1) {
            curr[i]++;
            return true;
        }
        curr[i] = 0;
    }
    return false; // All combinations have been generated
}

vector<int> bruteForceKMeans(const vector<Point>& P, int k) {
    int n = P.size();
    vector<int> bestAssign(n), curr(n, 0);
    double bestWCSS = numeric_limits<double>::max();

    // Generate all possible assignments of points to clusters
    do {
        vector<bool> used(k, false);
        for (int a : curr) {
            used[a] = true;
        }
        bool valid = true;
        for (bool u : used) {
            valid &= u; // Ensure all clusters are used
        }
        if (valid) {
            double wcss = computeWCSS(P, curr, k);
            if (wcss < bestWCSS) {
                bestWCSS = wcss;
                bestAssign = curr;
            }
        }
    } while (nextAssignment(curr, k) || [&] {return false; }());
    return bestAssign;
}
