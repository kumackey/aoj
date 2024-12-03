#include <iostream>
using namespace std;

#define MAX 1000000

int main() {
    int n, key;
    cin >> n;

    int BinaryHeap[MAX];

    for ( int i = 0; i < n; i++) {
        cin >> BinaryHeap[i+1];
    }

    for ( int i = 1; i <= n; i++) {
        cout << "node " << i << ": key = " << BinaryHeap[i] << ", ";
        if ( i > 1) {
            cout << "parent key = " << BinaryHeap[i/2] << ", ";
        }
        if ( 2*i <= n) {
            cout << "left key = " << BinaryHeap[2*i] << ", ";
        }
        if ( 2*i+1 <= n) {
            cout << "right key = " << BinaryHeap[2*i+1] << ", ";
        }
        cout << endl;
    }
    
    return 0;
}