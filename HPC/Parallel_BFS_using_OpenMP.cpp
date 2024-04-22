#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

// Define the graph as an adjacency list
vector<vector<int>> graph;

// Function to perform BFS
void parallelBFS(int start, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Explore neighbors of the current node in parallel
        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); ++i) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    // Example graph initialization
    int numNodes = 6;
    graph.resize(numNodes);
    graph[0] = {1, 2};
    graph[1] = {0, 3, 4};
    graph[2] = {0, 5};
    graph[3] = {1};
    graph[4] = {1};
    graph[5] = {2};

    // Parallel BFS
    vector<bool> visited(numNodes, false);
    parallelBFS(0, visited);

    // Print visited nodes
    cout << "Visited nodes: ";
    for (int i = 0; i < numNodes; ++i) {
        if (visited[i])
            cout << i << " ";
    }
    cout << endl;

    return 0;
}
