#include <iostream>
using namespace std;

#define NIL -1

struct Node {
    int parent;
    int leftChild;
    int rightSlbling;
    int depth;
};

string getType(Node node) {
    if (node.parent == NIL) {
        return "root";
    }

    if (node.leftChild == NIL) {
        return "leaf";
    }

    return "internal node";
}    

void print(Node node, int num, Node nodes[]) {
    cout << "node " << num << ": ";
    cout << "parent = " << node.parent << ", ";
    cout << "depth = " << node.depth << ", ";
    cout << getType(node) << ", ";
    cout << "[";
    int child = node.leftChild;
    for (int i = 0; child != NIL; i++) {
        if (i != 0) {
            cout << ", ";
        }
        cout << child;
        child = nodes[child].rightSlbling;
    }
    cout << "]" << endl;
}


void setDepth(int current, int value, Node nodes[]) {
    nodes[current].depth = value;
    if (nodes[current].rightSlbling != NIL) {
        setDepth(nodes[current].rightSlbling, value, nodes);
    }
    if (nodes[current].leftChild != NIL) {
        setDepth(nodes[current].leftChild, value + 1, nodes);
    }
}

int main() {
    int n;
    cin >> n;

    Node nodes[n]; 

    for (int i = 0; i < n; i++) {
        Node node;
        node.parent = NIL;
        node.leftChild = NIL;
        node.rightSlbling = NIL;
        node.depth = 0;
        nodes[i] = node;
    }

    int id, k, child, currentChild, root;

    for (int i = 0; i < n; i++) {
        cin >> id >> k;
        // 次数kの分だけループする
        for (int j = 0; j < k; j++) {
            cin >> child;
            if (j == 0) {
                // 最初の子供は左の子供
                nodes[id].leftChild = child;
            } else {
                // 2つ目以降の子供は右の兄弟
                nodes[currentChild].rightSlbling = child;
            }
            nodes[child].parent = id;
            currentChild = child;
        }
    }

    for (int i = 0; i < n; i++) {
        if (nodes[i].parent == NIL) {
            root = i;
            break;
        }
    }

    setDepth(root, 0, nodes);

    for (int i = 0; i < n; i++) {
        print(nodes[i], i, nodes);
    }

    return 0;
}