#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100003;
const ll _INF = LLONG_MIN;
int parent[MAXN];
ll dist[MAXN];
bool hasCycle = false;

struct Edge {
    int u, v;
    ll w;
};
vector<Edge> Node[MAXN];
bool compare(ll &lhs, ll &rhs) { return lhs > rhs; }

void Relax(int from, int to, int weight) {
    if (dist[from] == _INF) return;
    // find valuable path
    if (dist[to] < dist[from] + weight) {
        dist[to] = dist[from] + weight;
        // parent[to] = from;
    }
}

ll BellmanFord(int start, int n) {
    // initialize
    for (int i = 0; i <= n; i++) {
        // parent[i] = -1;
        dist[i] = 0;
    }
    dist[start] = 0;
    // parent[start] = start;
    // iterate n-1 times(for n nodes)
    for (int i = 1; i <= n - 1; i++) {
        // for each edge belonging to Node[n]
        for (int j = 1; j <= n; j++) {
            for (Edge &e : Node[j]) Relax(e.u, e.v, e.w);
        }
    }
    // check if there exists positive cycle
    for (int i = 1; i <= n; i++) {
        for (Edge &e : Node[i])
            if (dist[e.v] < dist[i] + e.w) {
                hasCycle = true;
                return 0;  // find cycle!
            }
    }
    // find maximum dist
    // for (int i = 0; i <= n; i++) {
    //     cout << i << ": ";
    //     cout << dist[i] << endl;
    // }
    sort(dist + 1, dist + n + 1, compare);
    return dist[1];
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int _u, _v;
        ll _w;
        cin >> _u >> _v >> _w;
        Node[_u].push_back({_u, _v, _w});
    }
    ll max_result = BellmanFord(1, n);
    if (hasCycle)
        cout << "INF" << endl;
    else
        cout << max_result << endl;
    return 0;
}