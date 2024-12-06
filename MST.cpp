#include <bits/stdc++.h>
using namespace std;

// Disjoint Set for Union-Find operations
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findParent(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ultimate_u = findParent(u);
        int ultimate_v = findParent(v);
        if (ultimate_u == ultimate_v) return;

        if (rank[ultimate_u] < rank[ultimate_v]) {
            parent[ultimate_u] = ultimate_v;
        }
        else if (rank[ultimate_v] < rank[ultimate_u]) {
            parent[ultimate_v] = ultimate_u;
        }
        else {
            parent[ultimate_v] = ultimate_u;
            rank[ultimate_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ultimate_u = findParent(u);
        int ultimate_v = findParent(v);
        if (ultimate_u == ultimate_v) return;

        if (size[ultimate_u] < size[ultimate_v]) {
            parent[ultimate_u] = ultimate_v;
            size[ultimate_v] += size[ultimate_u];
        }
        else {
            parent[ultimate_v] = ultimate_u;
            size[ultimate_u] += size[ultimate_v];
        }
    }
};

class Solution {
public:
    // Function to find the sum of weights of edges in the Minimum Spanning Tree
    int findMST(int nodes, vector<vector<int>> graph[]) {
        vector<pair<int, pair<int, int>>> edges;

        // Convert adjacency list to edge list
        for (int i = 0; i < nodes; i++) {
            for (auto it : graph[i]) {
                int neighbor = it[0];
                int weight = it[1];
                int current = i;

                edges.push_back({weight, {current, neighbor}});
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end());

        DisjointSet ds(nodes);
        int mstWeight = 0;

        // Kruskal's algorithm
        for (auto edge : edges) {
            int weight = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;

            // If nodes belong to different components, add edge to MST
            if (ds.findParent(u) != ds.findParent(v)) {
                mstWeight += weight;
                ds.unionBySize(u, v);
            }
        }

        return mstWeight;
    }
};

int main() {
    int nodes = 5;
    vector<vector<int>> inputEdges = {{0, 1, 2}, {0, 2, 1}, {1, 2, 1}, {2, 3, 2}, {3, 4, 1}, {4, 2, 2}};
    vector<vector<int>> graph[nodes];

    for (auto edge : inputEdges) {
        vector<int> temp(2);
        temp[0] = edge[1];
        temp[1] = edge[2];
        graph[edge[0]].push_back(temp);

        temp[0] = edge[0];
        temp[1] = edge[2];
        graph[edge[1]].push_back(temp);
    }

    Solution obj;
    int mstWeight = obj.findMST(nodes, graph);
    cout << "The total weight of the MST is: " << mstWeight << endl;

    return 0;
}
