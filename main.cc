#include <iostream>
#include <vector>
#include <algorithm> // std::findを使用するために必要
using namespace std;

bool solve(int i, int m, vector<int> &a) {
    if (m == 0) return true;
    if (i >= a.size()) return false;
    return solve(i+1, m, a) || solve(i+1, m-a[i], a);
}

int main() {
    int n, q;
    
    // 最初のリストの入力
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    // 二番目のリストの入力
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int M;
        cin >> M;
        if (solve(0, M, A)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}