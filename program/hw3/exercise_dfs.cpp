#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100003;

struct Edge {
    int u, v;
    // ll w;
};

// add edge
// G[u].push_back({u, v, w});
// G[v].push_back({v, u, w});
int n, m;
vector<Edge> G[MAXN];
bool visit[MAXN];
int tin[MAXN], tout[MAXN], time_stamp = 0;
string vertexStr, targetStr;
unordered_set<char> targetSet;
unordered_set<char> originSet;
bool found = 0;

void DFS(int u) {
    visit[u] = 1;
    if (targetSet.count(vertexStr[u - 1]) > 0) {
        targetSet.erase(vertexStr[u - 1]);
    }

    if (targetSet.empty()) {
        found = 1;
        return;
    }
    // tin[u] = time_stamp++;
    for (Edge &e : G[u])
        if (!visit[e.v]) {
            DFS(e.v);
        }
    // tout[u] = time_stamp++;
}

int main() {
    // input

    cin >> n >> m;
    cin >> vertexStr;

    for (int i = 0; i < m; i++) {
        int _u, _v;
        cin >> _u >> _v;
        G[_u].push_back({_u, _v});
        G[_v].push_back({_v, _u});
    }
    cin >> targetStr;
    for (int j = 0; j < targetStr.length(); j++) {
        originSet.insert(targetStr[j]);
    }

    // algo start
    for (int i = 1; i <= n; i++) {
        if (found) break;
        if (visit[i]) continue;
        targetSet = originSet;
        DFS(i);
    }
    if (found)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}