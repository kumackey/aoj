#include <iostream>
using namespace std;

#define NIL -1

struct Node {
    int key;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
};

Node *root, *NIL_NODE;

void insert(int key) {
    Node *y = NIL_NODE;
    Node *x = root;
    Node *z = new Node;

    z->key = key;
    z->leftChild = NIL_NODE;
    z->rightChild = NIL_NODE;

    while ( x != NIL_NODE ) {
        y = x;
        if ( z->key < x->key ) {
            x = x->leftChild;
        } else {
            x = x->rightChild;
        }
    }
    z->parent = y;

    if ( y == NIL_NODE ) {
        root = z;
    } else if ( z->key < y->key ) {
        y->leftChild = z;
    } else {
        y->rightChild = z;
    }
}

void find(int key) {
    Node *u = root;
    while ( u != NIL_NODE && u->key != key ) {
        if ( key < u->key ) {
            u = u->leftChild;
        } else {
            u = u->rightChild;
        }
    }
    if ( u != NIL_NODE ) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
}

void inorder(Node *u) {
    if ( u == NIL_NODE ) return;
    inorder(u->leftChild);
    cout << " " << u->key;
    inorder(u->rightChild);
}

void preorder(Node *u) {
    if ( u == NIL_NODE ) return;
    cout << " " << u->key;
    preorder(u->leftChild);
    preorder(u->rightChild);
}

void print() {
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
}

int main() {
    int n, key;
    cin >> n;
    string command;
    
    for (int i = 0; i < n; i++) {
        cin >> command;
        if (command == "insert") {
            scanf("%d", &key);
            insert(key);
        } else if (command == "find") {
            scanf("%d", &key);
            find(key);
        } else if (command == "print") {
            print();
        }
    }

    return 0;
}