#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int MAX = 100;
vector<int> adj[MAX];           // Adjacency list
double dist[MAX][MAX];          // Distance between nodes
double shortD[MAX];             // Shortest distance from source
bool vis[MAX];                  // Visited array
string path[MAX];               // Path from source

int main() {
    int n = 8; // A to H

    // Initialize distance matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : INT_MAX;

    // Initialize adjacency and weights manually
    adj[0] = {1, 2, 4};    dist[0][1] = 17;   dist[0][2] = 5.7;   dist[0][4] = 3.8;
    adj[1] = {5};          dist[1][5] = 4;
    adj[2] = {3};          dist[2][3] = 7.3;
    adj[4] = {6};          dist[4][6] = 14.2;
    adj[6] = {7};          dist[6][7] = 2;

    adj[3] = {};
    adj[5] = {};
    adj[7] = {};

    // Initialization
    for (int i = 0; i < n; i++) {
        shortD[i] = INT_MAX;
        vis[i] = false;
        path[i] = "";
    }

    auto start_time = high_resolution_clock::now();

    // BFS using queue
    queue<pair<int, double>> q;
    q.push({0, 0}); // Start at node A (index 0)
    path[0] = "A";
    shortD[0] = 0;

    while (!q.empty()) {
        auto [node, curr_dist] = q.front();
        q.pop();

        if (vis[node]) continue;
        vis[node] = true;

        for (int i = 0; i < adj[node].size(); i++) {
            int next = adj[node][i];
            double next_dist = curr_dist + dist[node][next];

            if (shortD[next] > next_dist) {
                shortD[next] = next_dist;
                path[next] = path[node] + "->" + char(next + 'A');
                q.push({next, next_dist});
            }
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    // Output
    cout << "Breadth First Search\n" << endl;

    cout << left << setw(8) << "Node"
         << setw(12) << "Distance"
         << "Path" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(8) << char('A' + i)
             << setw(12) << shortD[i]
             << path[i] << endl;
    }

    cout << "\nExecution Time: " << duration.count() << " microseconds" << endl;

    return 0;
}