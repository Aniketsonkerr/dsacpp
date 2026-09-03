#include <iostream>
#include <vector>

using namespace std;

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

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

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
        return root;

    updateHeight(root);
    int balance = getBalanceFactor(root);

    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* findMin(Node* root) {
    Node* current = root;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* deleteAVL(Node* root, int key, string &rotationAction) {
    if (root == nullptr) return nullptr;

    if (key < root->key) {
        root->left = deleteAVL(root->left, key, rotationAction);
    } else if (key > root->key) {
        root->right = deleteAVL(root->right, key, rotationAction);
    } else {
        // Node found
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key, rotationAction);
        }
    }

    if (root == nullptr) return root;

    updateHeight(root);
    int balance = getBalanceFactor(root);

    // Rebalance if unbalanced
    if (balance > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            rotationAction = "LL Rotation (Right Rotate)";
            return rotateRight(root);
        } else {
            rotationAction = "LR Rotation (Left-Right Rotate)";
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }

    if (balance < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            rotationAction = "RR Rotation (Left Rotate)";
            return rotateLeft(root);
        } else {
            rotationAction = "RL Rotation (Right-Left Rotate)";
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
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
    cout << "        PART B: AVL TREE DELETION       \n";
    cout << "========================================\n\n";

    vector<int> initialKeys = {10, 20, 30, 40, 50, 25};
    Node* root = nullptr;

    for (int key : initialKeys) {
        root = insertAVL(root, key);
    }

    cout << "Tree created with keys: 10, 20, 30, 40, 50, 25\n";
    cout << "Inorder before deletion: ";
    printInorder(root);
    cout << "\nHeight before deletion: " << getHeight(root) << "\n\n";

    vector<int> deleteKeys = {50, 40};

    cout << "--- Executing Deletions ---\n";
    for (int key : deleteKeys) {
        string rotationAction = "None (Balanced)";
        root = deleteAVL(root, key, rotationAction);

        cout << "Deleted Key: " << key << "\n";
        cout << "Rotation Executed: " << rotationAction << "\n";
        cout << "Inorder Traversal: ";
        printInorder(root);
        cout << "\nCurrent Tree Height: " << getHeight(root) << "\n";
        cout << "Root Balance Factor: " << getBalanceFactor(root) << "\n";
        cout << "----------------------------------------\n";
    }

    freeAVL(root);
    return 0;
}