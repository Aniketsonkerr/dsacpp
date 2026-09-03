#include <iostream>
#include <vector>

using namespace std;

// Rotation counters
int ll_count = 0;
int rr_count = 0;
int lr_count = 0;
int rl_count = 0;

int getMax(int a, int b) {
    return (a > b) ? a : b;
}

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int val) {
        key = val;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    if (node != nullptr) {
        node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
    }
}

// Single Right Rotation (LL Case)
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Single Left Rotation (RR Case)
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insertAVL(Node* root, int key) {
    if (root == nullptr) return new Node(key);

    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else if (key > root->key)
        root->right = insertAVL(root->right, key);
    else
        return root; // Duplicates ignored

    updateHeight(root);
    int balance = getBalanceFactor(root);

    // Left Left Case -> Single Right Rotation
    if (balance > 1 && key < root->left->key) {
        ll_count++;
        return rotateRight(root);
    }

    // Right Right Case -> Single Left Rotation
    if (balance < -1 && key > root->right->key) {
        rr_count++;
        return rotateLeft(root);
    }

    // Left Right Case -> Double Rotation (Left then Right)
    if (balance > 1 && key > root->left->key) {
        lr_count++;
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case -> Double Rotation (Right then Left)
    if (balance < -1 && key < root->right->key) {
        rl_count++;
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void printInorder(Node* root) {
    if (root == nullptr) return;
    printInorder(root->left);
    cout << root->key << " ";
    printInorder(root->right);
}

void freeAVL(Node* root) {
    if (root == nullptr) return;
    freeAVL(root->left);
    freeAVL(root->right);
    delete root;
}

int main() {
    cout << "========================================\n";
    cout << "     PART A: AVL TREE CONSTRUCTION      \n";
    cout << "========================================\n\n";

    // Sequence designed to trigger LL, RR, LR, and RL rotations
    vector<int> inputSequence = {30, 20, 10, 40, 50, 25, 27};
    Node* root = nullptr;

    cout << "Input Sequence: ";
    for (int key : inputSequence) {
        cout << key << " ";
        root = insertAVL(root, key);
    }
    cout << "\n\n";

    cout << "Inorder Traversal: ";
    printInorder(root);
    cout << "\n";

    cout << "Height of Final Tree: " << getHeight(root) << "\n\n";

    cout << "--- Rotations Performed ---\n";
    cout << "LL Rotations: " << ll_count << "\n";
    cout << "RR Rotations: " << rr_count << "\n";
    cout << "LR Rotations: " << lr_count << "\n";
    cout << "RL Rotations: " << rl_count << "\n";
    cout << "Total Rotations: " << (ll_count + rr_count + lr_count + rl_count) << "\n";

    freeAVL(root);
    return 0;
}