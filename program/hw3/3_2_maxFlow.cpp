#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100003;
#define INF 1000000

struct Edge {
    int u, v;
    int capacity;
    Edge *rev;
};
vector<Edge> edge[MAXN];
vector<int> bottleNeck(target + 1, 0);
ll total_health = 0;

int BFS(int source, int target, vector<Edge *> from) {
    vector<bool> visit(target + 1, 0);
    int minEdge = INF;
    queue<int> que;
    que.push(source);
    visit[source] = 1;
    while (que.size()) {
        int u = que.front();
        que.pop();
        for (Edge &e : edge[u])
            if (!visit[e.v] && e.capacity > 0) {
                que.push(e.v);
                visit[e.v] = 1;
                from[e.v] = &e;
                minEdge = min(minEdge, e.capacity);
            }
    }
    cout << "bfs" << endl;
    cout << "visit[target: " << visit[target] << endl;
    if (visit[target])  // there exists a path from s to t
        return minEdge;
    else
        return 0;
}

bool Fork_Fulkerson(int source, int target) {
    vector<Edge *> from(target + 1, nullptr);
    while (BFS(source, target, from)) {
        int residual_cap = BFS(source, target, from);
        int current = target;
        while (current != source) {
            // cout << target << endl;
            cout << residual_cap << endl;
            from[current]->capacity -= residual_cap;
            // edge[current].capacity += residual_cap;
            cout << "rev.u: " << from[current]->rev->v << endl;
            from[current]->rev->capacity += residual_cap;
            current = from[current]->u;
        }
    }
    return total_health == 0;
}

int main() {
    int n, m, source = 0, target = 0, cnt = 0;
    cin >> n >> m;
    int r[n + 1]{0}, c[n + 1]{0}, d[m + 1]{0};
    for (int i = 0; i < MAXN; i++) {
        edge[i].reserve(m);
    }
    target = 2 * n + m + 1;

    for (int i = 1; i <= n; i++) {
        int s_r_cap;
        cnt++;
        r[i] = cnt;
        cin >> s_r_cap;
        // s -> r
        edge[0].push_back({0, r[i], s_r_cap, 0});
        // 反向
        edge[r[i]].push_back({r[i], 0, 0, 0});
        // rev
        edge[0].back().rev = &edge[r[i]].back();
        edge[r[i]].back().rev = &edge[0].back();
    }
    for (int i = 1; i <= n; i++) {
        int s_c_cap;
        cnt++;
        c[i] = cnt;
        cin >> s_c_cap;
        // s -> c
        edge[0].push_back({0, c[i], s_c_cap, 0});
        // 反向
        edge[c[i]].push_back({c[i], 0, 0, 0});
        // rev
        edge[0].back().rev = &edge[c[i]].back();
        edge[c[i]].back().rev = &edge[0].back();
    }
    for (int i = 1; i <= m; i++) {
        int _r, _c, rc_d_cap;
        cnt++;
        d[i] = cnt;
        cin >> _r >> _c >> rc_d_cap;
        // r -> d
        edge[r[_r]].push_back({r[_r], d[i], INF, 0});
        // r -> d 反向
        edge[d[i]].push_back({d[i], r[_r], 0, 0});
        // rev
        edge[r[_r]].back().rev = &edge[d[i]].back();
        edge[d[i]].back().rev = &edge[r[_r]].back();
        //-----------
        // c -> d
        edge[c[_c]].push_back({c[_c], d[i], INF, 0});
        // c -> d 反向
        edge[d[i]].push_back({d[i], c[_c], 0, 0});
        // rev
        edge[c[_c]].back().rev = &edge[d[i]].back();
        edge[d[i]].back().rev = &edge[c[_c]].back();
        //-----------
        // d -> t
        edge[d[i]].push_back({d[i], target, rc_d_cap, 0});
        // d -> t 反向
        edge[target].push_back({target, d[i], 0, 0});
        // rev
        edge[d[i]].back().rev = &edge[target].back();
        edge[target].back().rev = &edge[d[i]].back();
        //-----------
        // 總血量
        total_health += rc_d_cap;
    }
    cout << target << endl;
    for (int i = 0; i <= target; i++) {
        cout << i << ": ";
        cout << edge[i].back().rev->u << endl;
    }
    if (Fork_Fulkerson(source, target))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}