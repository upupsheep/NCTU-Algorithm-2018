#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100003;

struct Edge {
    int u, v;
    // ll w;
};
struct ToutTime {
    int idx;
    int val;
};

// add edge
// G[u].push_back({u, v, w});
// G[v].push_back({v, u, w});
int n, m;
vector<Edge> G[MAXN], G_T[MAXN];
ToutTime tout[MAXN];
bool visit[MAXN] = {0}, visit_T[MAXN] = {0};
int tin[MAXN], time_stamp = 0;
string vertexStr, targetStr;
unordered_set<char> targetSet, originSet;
bool found = 0;

bool compare(ToutTime &lhs, ToutTime &rhs) { return lhs.val > rhs.val; }

void DFS(int u) {
    visit[u] = 1;
    tin[u] = time_stamp++;
    for (Edge &e : G[u])
        if (!visit[e.v]) {
            DFS(e.v);
        }
    tout[u].idx = u;
    tout[u].val = time_stamp++;
}

void DFS_T(int u) {
    visit_T[u] = 1;
    if (targetSet.count(vertexStr[u - 1]) > 0) {
        targetSet.erase(vertexStr[u - 1]);
    }

    if (targetSet.empty()) {
        found = 1;
        return;
    }
    for (Edge &e : G_T[u])
        if (!visit_T[e.v]) {
            DFS_T(e.v);
        }
}

int main() {
    // input
    cin >> n >> m;
    cin >> vertexStr;

    // create direct graph G and G_T
    for (int i = 0; i < m; i++) {
        int _u, _v;
        cin >> _u >> _v;
        G[_u].push_back({_u, _v});
        G_T[_v].push_back({_v, _u});
    }
    cin >> targetStr;
    for (int j = 0; j < targetStr.length(); j++) {
        originSet.insert(targetStr[j]);
    }

    /*** algo start ***/
    // DFS for G
    for (int i = 1; i <= n; i++) {
        // if (found) break;
        if (visit[i]) continue;
        // targetSet = originSet;
        DFS(i);
    }
    // sort by tout order(from big to small)
    sort(tout + 1, tout + n + 1, compare);
    // DFG for G_T(by tout order)
    for (int i = 1; i <= n; i++) {
        if (found) break;
        if (visit_T[tout[i].idx]) continue;
        targetSet = originSet;
        DFS_T(tout[i].idx);
    }
    // output
    if (found)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}