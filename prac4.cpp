#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int u; // start vertex
    int v; // end vertex
    int weight; // weight of the edge
};

void BellmanFord(const vector<Edge>& edges, int V, int source) { // int V = number of vertices 

    // Step 1: Initialize distances from source to all vertices as infinity
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;
    // We create a distance array where each position represents the shortest distance from the source to that vertex. We initialize all distances to "infinity" (INT_MAX) because initially, we assume all vertices are unreachable. The distance to the source itself is 0.


    // Step 2: relax all V-1 edges
    for(int i = 1; i <= V-1; ++i) {
        for(const Edge& edge : edges) {
            if(distance[edge.u] != INT_MAX && // Is the distance to the starting vertex (u) known (not infinity)?
                distance[edge.u] + edge.weight < distance[edge.v]) // If we add the weight of the edge to the distance to u, is that less than the current known distance to v?
                {
                    distance[edge.v] = distance[edge.u] + edge.weight;
                }
        }
    }

    // Step 3: check for negative cycles
    // After relaxing all edges, we perform one more check on all edges to see if we can still improve any distance. If we can, that means there is a negative weight cycle, and we print a message.
    for(const Edge& edge : edges) {
    if(distance[edge.u] != INT_MAX &&
    distance[edge.u] + edge.weight < distance[edge.v]) {
        cout << "Graph contains a negative-weight cycle ";
        return;
    }
}

    // Print the shortest distances from the source
    cout << "Vertex Distance from Source (" << source << ")\n";
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << distance[i] << "\n"; // Output distances
    }

}


int main() {

    int V = 5; // number of vertices
    vector<Edge> edges; // to hold the edges

    // adding edges
    edges.push_back({0, 1, 6});
    edges.push_back({0, 2, 7});
    edges.push_back({1, 2, 8});
    edges.push_back({1, 3, 5});
    edges.push_back({1, 4, -4});
    edges.push_back({2, 3, -3});
    edges.push_back({2, 4, 9});
    edges.push_back({3, 1, -2});
    edges.push_back({4, 0, 2});
    edges.push_back({4, 3, 7});

    BellmanFord(edges, V, 0);

    return 0;

}