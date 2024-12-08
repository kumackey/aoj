#include <iostream>
#include <queue>
using namespace std;

struct Color{
    string color;
    int d;
};

#define NIL -1
int M[101][101];

Color discover(Color color, int d) {
    color.color = "gray";
    color.d = d;
    return color;
}

void bfs(int n, Color colors[]) {
    queue<int> q;
    colors[0] = discover(colors[0], 0);
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (M[u][v] == 1 && colors[v].color == "white") {
                colors[v] = discover(colors[v], colors[u].d + 1);
                q.push(v);
            }
        }
        colors[u].color = "black";
    }
}


int main() {
    int n;
    cin >> n;

    Color colors[n];

    for (int i = 0; i < n; i++) {
        // initialize the matrix
        for (int j = 0; j < n; j++) {
            M[i][j] = 0;
        }

        // initialize the colors
        colors[i].color = "white";
        colors[i].d = -1;

        int vn, en;
        cin >> vn >> en;
        for (int j = 0; j < en; j++) {
            int e;
            cin >> e;
            M[vn-1][e-1] = 1;
        }
    }

    bfs(n, colors);

    for (int i = 0; i < n; i++) {
        cout << i+1 << " " << colors[i].d << endl;
    }

    return 0;
}
