#include <iostream>
#include <string>
#include <climits>
using namespace std;

#define MAX 101

int M[MAX][MAX];

int matrixChainMuutiplication(int ps[], int n) {
    for (int i=1; i<=n; i++) {
        M[i][i] = 0;
    }

    for (int l=2; l<=n; l++) {
        for (int i=1; i<=n-l+1; i++) {
            int j =i+l-1;
            M[i][j] = INT_MAX;
            for (int k=i; k<=j-1; k++) {
                M[i][j] = min(M[i][j], M[i][k] + M[k+1][j] + ps[i-1]*ps[k]*ps[j]);
            }
        }
    }

    return M[1][n];
}

int main() {
    int n;
    scanf("%d", &n);

    int ps[n+1];

    for (int i=0; i<n; i++) {
        cin >> ps[i];
        int tmp = 0;
        cin >> tmp;
        if (i == n-1) {
            ps[i+1] = tmp;
        }
    }

    printf("%d\n", matrixChainMuutiplication(ps, n));

    return 0;
}