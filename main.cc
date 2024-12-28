#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

#define INFTY (1 << 30)
#define MAX 100000

class Edge {
public:
    int t, w;
    Edge() {}
    Edge(int t, int w) : t(t), w(w) {}
};

vector<Edge> G[MAX];
int n, d[MAX];

void bfs(int s) {
    for (int i = 0; i < n; i++) d[i] = INFTY;
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    int u;
    while (!Q.empty()) {
        u = Q.front(); Q.pop();
        for (int i = 0; i < G[u].size(); i++) {
            Edge e = G[u][i];
            if ( d[e.t] == INFTY ) {
                d[e.t] = d[u] + e.w;
                Q.push(e.t);
            }
        }
    }
}

void solve() {
    bfs(0);
    int maxv = 0;
    int tgt = 0;
    for ( int i =0; i < n; i++) {
        if (d[i] == INFTY) continue;
        if (maxv < d[i]) {
            maxv = d[i];
            tgt = i;
        }
    }

    bfs(tgt);
    maxv = 0;
    for ( int i =0; i < n; i++) {
        if (d[i] == INFTY) continue;
        if (maxv < d[i]) {
            maxv = d[i];
        }
    }

    cout << maxv << endl;
}

int main() {
    int s, t, w;
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        cin >> s >> t >> w;
        G[s].push_back(Edge(t, w));
        G[t].push_back(Edge(s, w));
    }
    solve();
}
