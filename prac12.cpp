// Write a program to implement Kruskal’s algorithm using Union Find Data Structure.

#include <bits/stdc++.h>
using namespace std;
class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0); // why n+1? => imagine it's a 1 based indexing graph
        // initially ranks will be marked 0
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; // initially parents will be marked with themselves
        }
    }

    // PATH COMPRESSION
    int findUPar(int node) { // find ultimate parent 
        if (node == parent[node]) 
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ultimate_u = findUPar(u);
        int ultimate_v = findUPar(v);
        if (ultimate_u == ultimate_v)  // when they belong to same component
            return;
        if (rank[ultimate_u] < rank[ultimate_v]) { // when they do not belong to same component
        // if u is smaller than v
            parent[ultimate_u] = ultimate_v;  // u will go and get connect to v
        }
        else if (rank[ultimate_v] < rank[ultimate_u]) { // if v is smaller than u
            parent[ultimate_v] = ultimate_u; // v will go and get connect to u
        }
        else {
            parent[ultimate_v] = ultimate_u; // same rank => can connect u to v or v to u
            rank[ultimate_u]++;
        }
    }
};
int main() {
    DisjointSet ds(7);
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);
    // if 3 and 7 have same parent or not
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same parent before connecting \n";
    }
    else cout << "Not same parent before connecting\n";

    ds.unionByRank(3, 7); // after connecting them to each other 

    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same parent after connecting\n";
    }
    else cout << "Not same parent after connecting\n";
    return 0;
}