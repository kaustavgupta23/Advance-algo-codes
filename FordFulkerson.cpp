#include <bits/stdc++.h>
using namespace std;

// Function for BFS to find if there is a path from source to sink
bool bfs(vector<vector<int>>& residualgraph, int source, int sink, vector<int>& parent) {
    int vert = residualgraph.size();  // Get the number of vertices
    vector<bool> visited(vert, false);  // Track visited nodes

    queue<int> q;  // Queue to perform BFS

    q.push(source);  // Start BFS from the source
    parent[source] = -1;  // No parent for source
    visited[source] = true;  // Mark source as visited

    // While queue is not empty, explore all nodes
    while (!q.empty()) {
        int current = q.front();  // Get the front element
        q.pop();

        // Explore neighbors of the current node
        for (int next = 0; next < vert; next++) {
            // Check if the node is not visited and there is available capacity on the edge
            if (!visited[next] && residualgraph[current][next] > 0) {
                if (next == sink) {  // If we reach the sink, stop the search
                    parent[next] = current;
                    return true;
                }
                q.push(next);  // Add the node to the queue for further exploration
                parent[next] = current;  // Set the parent of the node
                visited[next] = true;  // Mark the node as visited
            }
        }
    }
    return false;  // No augmenting path found
}

// Ford-Fulkerson algorithm to find the maximum flow
int fordfulkerson(vector<vector<int>> graph, int src, int sink) {
    int vert = graph.size();  // Get the number of vertices
    vector<vector<int>> residualgraph = graph;  // Create a residual graph (initially same as original)
    vector<int> parent(vert, -1);  // To store the path

    int maxflow = 0;  // Initialize max flow to 0

    // While there is an augmenting path in the residual graph
    while (bfs(residualgraph, src, sink, parent)) {
        int path = INT_MAX;  // Initialize path flow as infinity

        // Find the minimum residual capacity of the path from source to sink
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            path = min(path, residualgraph[u][v]);  // Get the minimum flow along the path
        }

        // Update residual graph by reducing the capacity along the path and adding reverse flow
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            residualgraph[u][v] -= path;  // Reduce the forward edge capacity
            residualgraph[v][u] += path;  // Add the reverse edge capacity (for possible future flow)
        }

        maxflow += path;  // Add the flow in this iteration to maxflow
    }

    return maxflow;  // Return the total maximum flow
}

int main() {
    int vert;  // Number of vertices
    cout << "Enter number of vertices:";
    cin >> vert;

    // Initialize a graph represented as an adjacency matrix
    vector<vector<int>> graph(vert, vector<int>(vert, 0));

    // Input the graph as an adjacency matrix with edge capacities
    cout << "Enter adjacency matrix (edge capacity row by row):" << endl;
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            cin >> graph[i][j];
        }
    }

    int src, sink;
    cout << "Enter source vertex:";
    cin >> src;
    cout << "Enter sink vertex:";
    cin >> sink;

    // Call the Ford-Fulkerson function to find the maximum flow
    int maxflow = fordfulkerson(graph, src, sink);

    // Output the result
    cout << "Maximum flow:" << endl << maxflow << endl;
}


// output
// Enter number of vertices: 4
// Enter adjacent matrix(edge capacity row by row):
// 0 10 5 0
// 0 0 15 10
// 0 0 0 10
// 0 0 0 0
// Enter source vertex: 0
// Enter sink vertex: 3
