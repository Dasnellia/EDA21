#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node *root;
    Node *T_nil; // Sentinel

    void leftRotate(Node *x);
    void rightRotate(Node *x);
    void insertFixup(Node *z);
    void deleteFixup(Node *x);
    void transplant(Node *u, Node *v);
    Node* treeMinimum(Node *x);
    void printHelper(Node *node, string indent, bool last);

public:
    RBTree();
    void insert(int key);
    void remove(int key);
    void print();
};

RBTree::RBTree() {
    T_nil = new Node(0);
    T_nil->color = BLACK;
    root = T_nil;
}

void RBTree::leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != T_nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != T_nil) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBTree::insert(int key) {
    Node *z = new Node(key);
    z->left = z->right = T_nil;
    Node *y = nullptr;
    Node *x = root;

    while (x != T_nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    z->color = RED;
    insertFixup(z);
}

void RBTree::insertFixup(Node *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node* RBTree::treeMinimum(Node *x) {
    while (x->left != T_nil) {
        x = x->left;
    }
    return x;
}

void RBTree::transplant(Node *u, Node *v) {
    if (u->parent == nullptr) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void RBTree::deleteFixup(Node *x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::remove(int key) {
    Node *z = root;
    while (z != T_nil && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }
    if (z == T_nil) return;

    Node *y = z;
    Color y_original_color = y->color;
    Node *x;

    if (z->left == T_nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == T_nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK) deleteFixup(x);
}

void RBTree::printHelper(Node *node, string indent, bool last) {
    if (node != T_nil) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }
        string color = node->color == RED ? "RED" : "BLACK";
        cout << node->key << "(" << color << ")" << endl;
        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
}

void RBTree::print() {
    printHelper(root, "", true);
}

int main() {
    RBTree tree;
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(4);
    tree.insert(11);
    tree.insert(8);
    tree.insert(14);
    tree.insert(15);

    cout << "\nArbol despues de inserciones:" << endl;
    tree.print();

    tree.remove(7);
    //tree.remove(5);

    cout << "\nArbol despues de eliminaciones:" << endl;
    tree.print();

    return 0;
}
