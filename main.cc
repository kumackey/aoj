#include <iostream>
#include <string>
using namespace std;

#define MAX 1001
int LCS[MAX][MAX];

int lcs(string X, string Y) {
    int m = X.size();
    int n = Y.size();
    int max = 0;

    X = " " + X;
    Y = " " + Y;
    for (int i = 0; i < m; i++) {
        LCS[i][0] = 0;
    }
    for (int j = 0; j < n; j++) {
        LCS[0][j] = 0;
    }

    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            if (X[i] == Y[j]) {
                LCS[i][j] = LCS[i-1][j-1] + 1;
            } else if (LCS[i-1][j] >= LCS[i][j-1]) {
                LCS[i][j] = LCS[i-1][j];
            } else {
                LCS[i][j] = LCS[i][j-1];
            }

            if (LCS[i][j] > max) {
                max = LCS[i][j];
            }
        }
    }

    return max;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        cout << lcs(s1, s2) << endl;
    }

    return 0;
}