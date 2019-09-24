#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int M = N * (N - 1) / 2;
const int LEN = (1 << M);

bitset<LEN> B;

void readB() {
    string s;
    cin >> s;

    int i = LEN - 1;
    for (char c : s) {
        int x;
        if (0 <= c && c <= '9')
            x = c - '0';
        else
            x = c - 'A' + 10;
        for (int j = 0; j < 4; j++, i--) {
            B[i] = (x >> 3) & 1;
            x <<= 1;
        }
    }
}

bool TST(const vector<pair<int, int> > &edges) {
    // input: edge set of an 8 vertex simple graph G
    // output: return true if G contain a binary spanning tree, otherwise false
    // time complexity: O(m) where m = number of edge

    int G = 0;
    for (auto e : edges) {
        int u = e.first;
        int v = e.second;
        if (u > v) swap(u, v);
        int idx = v * (v - 1) / 2 + u;
        ;
        if (u == v) idx = -1;
        G |= (1 << idx);
    }
    return B[G];
}

// Complete the solve function below.
void solve() {
    vector<pair<int, int> > edges, v_edges;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;  // edge (u,v)
        edges.push_back({u, v});
    }
    v_edges = edges;
    for (int u = 0; u < 5; u++) {
        int dummy = 5, dam_dummy1 = 6, dam_dummy2 = 7;
        edges.push_back({u, dummy});
        edges.push_back({dummy, dam_dummy1});
        edges.push_back({dam_dummy1, dam_dummy2});
        if (TST(edges)) {
            // candidate
            // check if it's real yes
            bool isReal = true;
            for (int v = 0; v < 5; v++) {
                if (u != v) {
                    int dummyV = 5, damn_dummyV1 = 6, damn_dummyV2 = 7;
                    v_edges.push_back({v, dummyV});
                    v_edges.push_back({dummyV, damn_dummyV1});
                    v_edges.push_back({damn_dummyV1, damn_dummyV2});
                    if (!TST(v_edges)) {
                        // it's fake!!!
                        v_edges.pop_back();
                        v_edges.pop_back();
                        v_edges.pop_back();
                        isReal = false;
                        break;
                    } else {
                        v_edges.pop_back();
                        v_edges.pop_back();
                        v_edges.pop_back();
                    }
                }
            }
            if (isReal) {
                cout << "Yes" << endl;
                return;
            }
        }
        edges.pop_back();
        edges.pop_back();
        edges.pop_back();
    }
    cout << "No" << endl;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    readB();

    int T;
    cin >> T;
    while (T--) solve();
}