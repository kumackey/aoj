#include <iostream>
using namespace std;

#define MAX 101
#define INFINITY 1<<21
int M[MAX][MAX];

#define white 0
#define gray 1
#define black 2

void dijkstra(int n) {
    int color[MAX], d[MAX], p[MAX];

    for (int i = 0; i < n; i++) {
        color[i] = white;
        d[i] = INFINITY;
        p[i] = -1;
    }

    d[0] = 0;
    p[0] = -1;

    while (true) {
        int mincost = INFINITY;
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (color[i] != black && d[i] < mincost) {
                mincost = d[i];
                u = i;
            }
        }

        if (u == -1) break;

        color[u] = black;

        for (int v = 0; v < n; v++) {
            if (color[v] != black && M[u][v] != INFINITY) {
                if (d[u] + M[u][v] < d[v]) {
                    d[v] = d[u] + M[u][v];
                    p[v] = u;
                    color[v] = gray;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << " " << (d[i] == INFINITY ? -1 : d[i]) << endl;
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = INFINITY;
        }
    }

    int u, k, v, c;
    for (int i =0; i<n; i++) {
        cin >> u >> k;
        for (int j = 0; j<k; j++) {
            cin >> v >> c;
            M[u][v] = c;
        }
    }

    dijkstra(n);

    return 0;
}
