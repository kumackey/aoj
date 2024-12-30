#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 100000

class Edge {
public:
    int s, t, w;
    Edge() {}
    Edge(int s, int t, int w) : s(s), t(t), w(w) {}
};

class DisjointSet {
    public:
    vector<int> rank, p;
    DisjointSet() {}
    DisjointSet(int size) {
        rank.resize(size, 0);
        p.resize(size, 0);
        for (int i=0;i<size;i++) makeSet(i);
    }

    void makeSet(int x) {
        p[x] = x;
        rank[x] = 0;
    }

    bool same(int x, int y) {
        return findSet(x) == findSet(y);
    }

    void unite(int x, int y) {
        link(findSet(x), findSet(y));
    }

    void link(int x, int y) {
        if (rank[x]>rank[y]) {
            p[y] = x;
        } else {
            p[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }

    int findSet(int x) {
        if (x != p[x]) {
            p[x] = findSet(p[x]);
        }

        return p[x];
    }
};

int main() {
    int v, e, s, t, w;
    cin >> v >> e;
    vector<Edge> Edges(e);
    for (int i = 0; i < e; i++) {
        cin >> s >> t >> w;
        Edges[i] = Edge(s, t, w);
    }

    sort(Edges.begin(), Edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    DisjointSet ds(v);
    int sum = 0;
    for (int i = 0; i < e; i++) {
        Edge e = Edges[i];
        if (!ds.same(e.s, e.t)) {
            ds.unite(e.s, e.t);
            sum += e.w;
        }
    }
    
    cout << sum << endl;
    return 0;
}
