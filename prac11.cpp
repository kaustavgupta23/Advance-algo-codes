#include <iostream>
#include <vector>
#include <queue>
#include <climits> // For INT_MAX
#include <cstring> // For memset

using namespace std;

// Function to perform BFS and find an augmenting path
bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    int numVertices = residualGraph.size();
    vector<bool> visited(numVertices, false);
    
    // Create a queue for BFS
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1; // No parent for the source node

    // Standard BFS loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < numVertices; ++v) {
            // Check if v is not visited and there's capacity left
            if (!visited[v] && residualGraph[u][v] > 0) {
                // If we find the sink node, we stop and return true
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // No path found
    return false;
}

// Ford-Fulkerson algorithm to find the maximum flow
int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int numVertices = graph.size();
    // Create a residual graph and initialize it with the given capacities
    vector<vector<int>> residualGraph = graph;
    
    // This array is used to store the path found by BFS
    vector<int> parent(numVertices);

    int maxFlow = 0; // Initialize maximum flow

    // Augment the flow while there is an augmenting path
    while (bfs(residualGraph, source, sink, parent)) {
        // Find the minimum capacity (bottleneck) along the path found by BFS
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update the residual capacities and reverse flows along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow; // Reduce capacity
            residualGraph[v][u] += pathFlow; // Increase reverse flow
        }

        // Add path flow to the overall flow
        maxFlow += pathFlow;
    }

    // Return the total flow from source to sink
    return maxFlow;
}

int main() {
    // Sample graph represented as an adjacency matrix
    // 6 vertices: 0 is the source, 5 is the sink
    vector<vector<int>> graph = {
        {0, 16, 13, 0, 0, 0}, // Edges from vertex 0
        {0, 0, 10, 12, 0, 0}, // Edges from vertex 1
        {0, 4, 0, 0, 14, 0},  // Edges from vertex 2
        {0, 0, 9, 0, 0, 20},  // Edges from vertex 3
        {0, 0, 0, 7, 0, 4},   // Edges from vertex 4
        {0, 0, 0, 0, 0, 0}    // Edges from vertex 5 (sink)
    };

    int source = 0;
    int sink = 5;

    cout << "The maximum possible flow is: " << fordFulkerson(graph, source, sink) << endl;

    return 0;
}
