#include <bits/stdc++.h>
#include <iostream>
using namespace std;
class Node;

struct edge {
    Node *next;
    edge *rev;
    int capacity = 0;

    edge(Node *_next, int c) : next(_next), capacity(c) {}
    void set_rev(edge *_rev) {
        rev = _rev;
        rev->rev = this;
    }
};

class Node {
   public:
    int w, l, d;
    int bottleneck = INT_MAX;
    edge *from_edge;
    bool visited = 0;
    vector<edge *> edges;
    Node() {}
    Node(int _l, int _w, int _d) : w(_w), l(_l), d(_d) {}
};

Node s;
Node t;
vector<Node *> visited;
int flow = 0;

void reset(vector<Node *> &visited) {
    for (int i = 0; i < visited.size(); i++) {
        visited[i]->visited = 0;
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
            // cout << "found!" << endl;
            break;
        }
        // cout << "edges size: " << cur->edges.size() << endl;
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
            cur->from_edge->capacity -= 1;
            cur->from_edge->rev->capacity += 1;
            cur = cur->from_edge->rev->next;
        }
        flow += 1;
    }

    return flag;
}
int main() {
    /*
    // cout << pow(2, 25);
    int n;
    cin >> n;

    // B
    vector<Node *> boxes;
    vector<Node *> boxes2;
    for (int i = 0; i < n; i++) {
        int l, w, d;
        cin >> l >> w >> d;
        Node *box = new Node(l, w, d);
        boxes.push_back(box);

        // s -> boxes
        // s -> turret
        edge *starting_edge = new edge(box, 1);
        s.edges.push_back(starting_edge);
        edge *rev_s = new edge(&s, 0);
        starting_edge->set_rev(rev_s);

        Node *box2 = new Node(l, w, d);
        boxes2.push_back(box);
        // s -> turret
        edge *end_edge = new edge(&t, 1);
        box2->edges.push_back(end_edge);
        edge *rev_t = new edge(box2, 0);
        end_edge->set_rev(rev_t);
    }
    // edge *e = new edge(boxes[1], 1);
    // boxes[0]->edges.push_back(e);
    // edge *rev = new edge(boxes[0], 0);
    // e->set_rev(rev);
    // boxes[1]->edges.push_back(rev);

    for (int i = 0; i < boxes.size(); i++) {
        Node *box1 = boxes[i];
        for (int j = 0; j < boxes2.size(); j++) {
            Node *box2 = boxes2[j];
            if (box1->l < box2->l && box1->w < box2->w && box1->d < box2->d) {
                edge *e = new edge(box2, 1);
                box1->edges.push_back(e);
                edge *rev = new edge(box1, 0);
                e->set_rev(rev);
                box2->edges.push_back(rev);
            }
        }
    }
    */
    int n;
    cin >> n;
    vector<Node *> boxes;
    vector<Node *> boxes2;

    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        Node *box = new Node(a, b, c);
        boxes.push_back(box);

        box = new Node(a, b, c);
        boxes2.push_back(box);

        Node *b2 = boxes2[i];

        edge *end_edge = new edge(&t, 1);
        b2->edges.push_back(end_edge);
        edge *__rev = new edge(b2, 0);
        end_edge->set_rev(__rev);
    }

    for (int i = 0; i < boxes.size(); i++) {
        Node *b1 = boxes[i];

        edge *start_edge = new edge(b1, 1);
        s.edges.push_back(start_edge);
        edge *_rev = new edge(&s, 0);
        start_edge->set_rev(_rev);

        for (int j = 0; j < boxes2.size(); j++) {
            Node *b2 = boxes2[j];
            if (b1->l < b2->l && b1->w < b2->w && b1->d < b2->d) {
                edge *e = new edge(b2, 1);
                b1->edges.push_back(e);

                edge *rev = new edge(b1, 0);
                b2->edges.push_back(rev);

                e->set_rev(rev);
            }
        }
    }
    while (ford(&s)) {
    }

    // cout << flow << endl;
    cout << n - flow << endl;

    return 0;
}