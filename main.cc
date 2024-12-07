#include <iostream>
#include <stack>
using namespace std;

struct Color{
    string color;
    int d;
    int f;
};

#define NIL -1
int M[101][101];

Color discover(Color color, int time) {
    color.color = "gray";
    color.d = time;
    return color;
}

Color finish(Color color, int time) {
    color.color = "black";
    color.f = time;
    return color;
}

int nexT(int n, Color colors[], int u) {
    for (int i = 0; i < n; i++) {
        if (M[u][i] == 1 && colors[i].color == "white") {
            return i;
        }
    }
    return NIL;
}

void dfs(int n, Color colors[]) {
    stack<int> st;
    int time = 0;
    st.push(0);
    time++;
    colors[0] = discover(colors[0], time);
    while (!st.empty()) {
        int u = st.top();
        int v = nexT(n, colors, u);
        if (v != NIL) {
            if (colors[v].color == "white") {
                time++;
                colors[v] = discover(colors[v], time);
                st.push(v);
            }
        } else {
            time++;
            colors[u] = finish(colors[u], time);
            st.pop();
        }
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
        colors[i].d = 0;
        colors[i].f = 0;

        int vn, en;
        cin >> vn >> en;
        for (int j = 0; j < en; j++) {
            int e;
            cin >> e;
            M[vn-1][e-1] = 1;
            M[e-1][vn-1] = 1;
        }
    }

    dfs(n, colors);

    for (int i = 0; i < n; i++) {
        cout << i+1 << " " << colors[i].d << " " << colors[i].f << endl;
    }

    return 0;
}
