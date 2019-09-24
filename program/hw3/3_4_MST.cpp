#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef struct Edge Edge;
struct Edge {
    int u, v;
    ull w;
};
vector<Edge> edge;  // edge list

bool compare(Edge &lhs, Edge &rhs) { return lhs.w < rhs.w; }

// init: let root be itself
void init(int par[], int n) {
    for (int i = 1; i <= n; i++) par[i] = i;
}

// find: find set root
int find(int par[], int x) {
    if (par[x] == x) return x;
    return par[x] = find(par, par[x]);
}

// union: union two sets
void make_union(int par[], int u, int v) { par[find(par, u)] = find(par, v); }

/*
V: n
E: m
MST-KRUSKAL(G,w)
A={}
for each vertex v∈G.V
    MAKE-SET(v)
sort G.E by w
for each edge (u,v) ∈G.E
    if FIND-SET(u)≠FIND-SET(v)
        A=A⋃{(u,v)}
        UNION(u,v)
return A
*/
int MST_kruskal(int par[], int n, int m, int k) {
    init(par, n);
    sort(edge.begin(), edge.end(), compare);
    vector<ull> mst;
    for (int j = 0; j < m; j++) {
        // check whether exists cycle
        if (find(par, edge[j].u) == find(par, edge[j].v)) continue;
        // connect two set
        make_union(par, edge[j].u, edge[j].v);
        // add this edge-weight to the mst list
        mst.push_back(edge[j].w);
    }
    // find the k-th smallest edge-weight
    sort(mst.begin(), mst.end());
    return mst[k - 1];
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int parent_list[n + 1];
    for (int i = 0; i < m; i++) {
        int _u, _v;
        ull _w;
        cin >> _u >> _v >> _w;
        edge.push_back({_u, _v, _w});
    }
    cout << MST_kruskal(parent_list, n, m, k) << endl;
    return 0;
}