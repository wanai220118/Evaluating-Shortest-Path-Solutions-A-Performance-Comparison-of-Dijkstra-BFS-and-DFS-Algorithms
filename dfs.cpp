#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int MAX = 100;
vector<int> adj[MAX];         // Adjacency list
double dist[MAX][MAX];        // Distance between nodes
double shortD[MAX];           // Shortest distance from source
string path[MAX];             // Path from source

void DFS(int node, double curr_dist, string curr_path) {
    if (curr_dist < shortD[node]) {
        shortD[node] = curr_dist;
        path[node] = curr_path;
    }

    for (int i = 0; i < adj[node].size(); i++) {
        int next = adj[node][i];
        double next_dist = curr_dist + dist[node][next];

        if (next_dist < shortD[next]) {
            DFS(next, next_dist, curr_path + "->" + char(next + 'A'));
        }
    }
}

int main() {
    int n = 8; // A to H

    // Initialize distances
    for (int i = 0; i < n; i++) {
        shortD[i] = INT_MAX;
        path[i] = "";
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    // Define edges and distances
    adj[0] = {1, 2, 4};    dist[0][1] = 17;   dist[0][2] = 5.7;   dist[0][4] = 3.8;
    adj[1] = {5};          dist[1][5] = 4;
    adj[2] = {3};          dist[2][3] = 7.3;
    adj[4] = {6};          dist[4][6] = 14.2;
    adj[6] = {7};          dist[6][7] = 2;

    adj[3] = {};
    adj[5] = {};
    adj[7] = {};

    auto start_time = high_resolution_clock::now();

    DFS(0, 0, "A");

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    // Print title
    cout << "Depth First Search\n" << endl;

    // Tabular output
    cout << left << setw(10) << "Node"
         << setw(15) << "Distance"
         << "Path" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << char(i + 'A')
             << setw(15) << shortD[i]
             << path[i] << endl;
    }

    cout << "\nExecution Time: " << duration.count() << " microseconds" << endl;

    return 0;
}
