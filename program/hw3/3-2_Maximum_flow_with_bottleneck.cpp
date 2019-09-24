#include <bits/stdc++.h>
#include <iostream>
using namespace std;
class Node;

struct edge {
    Node *next;
    edge *rev;
    int capacity = 0;

    edge(Node *_next, int c)
        : next(_next)
        , capacity(c) {}
    void set_rev(edge *_rev) {
        rev = _rev;
        rev->rev = this;
    }
};

class Node {
public:
    int n;
    int bottleneck = INT_MAX;
    edge *from_edge;
    bool visited = 0;
    vector<edge *> edges;
    Node() {}
    Node(int _n)
        : n(_n) {}
};

Node s;
Node t;
vector<Node *> visited;
int flow = 0;

void reset(vector<Node *> &visited) {
    for (int i = 0; i < visited.size(); i++) {
        visited[i]->visited = 0;
        visited[i]->bottleneck = INT_MAX;
    }
    visited.clear();
}

// edge reset

bool ford(Node *s) {
    queue<Node *> que;
    que.push(s);

    reset(visited);
    visited.push_back(s);
    Node *cur;
    bool flag = 0;

    while (que.size()) {
        cur = que.front();
        que.pop();
        cur->visited = 1;

        if (cur == &t) {
            flag = 1;
            //cout << "found!" << endl;
            break;
        }
        //cout << "edges size: " << cur->edges.size() << endl;
        for (int i = 0; i < cur->edges.size(); i++) {
            edge *e = cur->edges[i];
            if (e->capacity > 0 && e->next->visited == 0) {
                e->next->visited = 1;
                visited.push_back(e->next);
                e->next->from_edge = e;
                e->next->bottleneck = min(e->capacity, cur->bottleneck);
                que.push(e->next);

                // speed up
                if (e->next == &t) {
                    flag = 1;
                    break;
                }
            }
        }
    }

    // backtrack
    if (flag) {
        cur = &t;
        int bottleneck = t.bottleneck;
        while (cur != s) {
            cur->from_edge->capacity -= bottleneck;
            cur->from_edge->rev->capacity += bottleneck;
            cur = cur->from_edge->rev->next;
        }
        flow -= bottleneck;
    }

    return flag;
}
int main() {
    cout << pow(2, 25);
    int n, m;
    cin >> n >> m;

    // row turrets
    vector<Node *> r_turrets;
    for (int i = 0; i < n; i++) {
        int bullets;
        cin >> bullets;
        Node *turret = new Node(bullets);
        r_turrets.push_back(turret);

        // s -> turret
        edge *starting_edge = new edge(turret, bullets);
        s.edges.push_back(starting_edge);
        edge *rev = new edge(&s, 0);
        starting_edge->set_rev(rev);
    }

    // col turrets
    vector<Node *> c_turrets;
    for (int i = 0; i < n; i++) {
        int bullets;
        cin >> bullets;
        Node *turret = new Node(bullets);
        c_turrets.push_back(turret);

        // s -> turret
        edge *starting_edge = new edge(turret, bullets);
        s.edges.push_back(starting_edge);
        edge *rev = new edge(&s, 0);
        starting_edge->set_rev(rev);
    }

    Node *dragons[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dragons[i][j] = nullptr;
        }
    }
    // dragons
    for (int i = 0; i < m; i++) {
        int bloods;
        int x, y;

        cin >> x >> y >> bloods;
        x--;
        y--;
        Node *dragon = new Node(bloods);
        //
        dragons[x][y] = dragon;

        // row -> dragon
        int r_bullet = r_turrets[x]->n;
        edge *r_edge = new edge(dragon, r_bullet);
        r_turrets[x]->edges.push_back(r_edge);

        edge *r_rev = new edge(r_turrets[x], 0);
        r_edge->set_rev(r_rev);
        dragon->edges.push_back(r_rev);

        //  col -> dragon
        int c_bullet = c_turrets[y]->n;
        edge *c_edge = new edge(dragon, c_bullet);
        c_turrets[y]->edges.push_back(c_edge);

        edge *c_rev = new edge(c_turrets[y], 0);
        c_edge->set_rev(c_rev);
        dragon->edges.push_back(c_rev);

        // dragon -> t
        edge *ending_edge = new edge(&t, bloods);
        dragon->edges.push_back(ending_edge);
        edge *rev = new edge(dragon, 0);
        ending_edge->set_rev(rev);
        flow += bloods;
    }
    //**
    //cout << c_turrets[2]->edges[2]->next->n << endl;
    //cout << c_turrets[2]->n << endl;

    // cout << "------" << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (dragons[i][j] == nullptr) {
    //             cout << "  ";
    //         } else
    //             cout << dragons[i][j]->edges.back()->capacity << " ";
    //     }
    //     cout << s.edges[i]->capacity;
    //     cout << endl;
    // }
    // for (int i = 0; i < n; i++) {
    //     cout << s.edges[n + i]->capacity << " ";
    // }
    // cout << endl;

    while (ford(&s)) {
        // cout << "------" << endl;
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         if (dragons[i][j] == nullptr) {
        //             cout << "  ";
        //         } else
        //             cout << dragons[i][j]->edges.back()->capacity << " ";
        //     }
        //     cout << s.edges[i]->capacity;
        //     cout << endl;
        // }
        // for (int i = 0; i < n; i++) {
        //     cout << s.edges[n + i]->capacity << " ";
        // }
        // cout << endl;
    }

    //cout << flow << endl;
    cout << ((flow == 0) ? "Yes" : "No") << endl;

    return 0;
}