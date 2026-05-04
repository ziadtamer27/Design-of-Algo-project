#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
using namespace std;

typedef vector<double> Point;
vector<int> kMeans(const vector<Point>& P, int k, int maxIterations);
int main() {
    cout << "====== ITERATIVE IMPROVEMENT (K-MEANS) ======" << endl;
    int n, k;
    cout << "Enter the number of points and clusters: ";
    cin >> n >> k;

    vector<Point> P(n);
    cout << "Enter the points (each point as space-separated values):" << endl;
    for (int i = 0; i < n; ++i) {
        P[i].resize(2); // Assuming 2D points for simplicity
        cin >> P[i][0] >> P[i][1];
    }

    vector<int> assign = kMeans(P, k, 300);
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

vector<int> kMeans(const vector<Point>& P, int k, int maxIterations = 300) {
    int n = P.size();
    mt19937 rng(42); // Fixed seed for reproducibility

    // k-means++ initialization
    vector<Point> Centroids;
    uniform_int_distribution<int> uid(0, n - 1);
    Centroids.push_back(P[uid(rng)]); // Randomly select the first centroid
    for (int i = 1; i < k; ++i) {
        vector<double> distances(n);
        double totalDist = 0.0;
        for (int j = 0; j < n; ++j) {
            double minDist = numeric_limits<double>::max();
            for (auto& centroid : Centroids) {
                double dist = distance(P[j], centroid);
                minDist = min(minDist, dist * dist); // Use squared distance
            }
            distances[j] = minDist;
            totalDist += minDist;
        }
        //Sample proportionally to the squared distance
        double r = uniform_real_distribution<>(0, totalDist)(rng);
        int chosen = -1;
        for (int idx = 0; idx < n; ++idx) {
            r -= distances[idx];
            if (r <= 0) {
                Centroids.push_back(P[idx]);
                break;
            }
        }
        if (chosen != -1) Centroids.push_back(P[chosen]);
    }

    vector<int> assignment(n, 0), newAssignment(n, 0);
    for (int iter = 0; iter < maxIterations; iter++) {
        // Assignment step
        for (int i = 0; i < n; ++i) {
            double minDist = numeric_limits<double>::max();
            for (int j = 0; j < k; ++j) {
                double dist = distance(P[i], Centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    newAssignment[i] = j;
                }
            }
        }
        if (newAssignment == assignment) break; // Convergence
        assignment = newAssignment;

        // Update step
        for (int i = 0; i < n; ++i) {
            double best = numeric_limits<double>::max();
            vector<Point> clusterPoints;
            for (int j = 0; j < k; j++) {
                if (assignment[j] == i) {
                    clusterPoints.push_back(P[j]);
                }
            }
            if (!clusterPoints.empty()) Centroids[i] = calculateCentroid(clusterPoints);
        }

    }
    return assignment;
}