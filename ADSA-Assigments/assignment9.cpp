#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;

// ==========================================
// PART A & B: 2-3 TREE IMPLEMENTATION
// ==========================================

struct Node23 {
    vector<int> keys;
    vector<Node23*> children;
    bool isLeaf;

    Node23(bool leaf = true) : isLeaf(leaf) {}
    ~Node23() {
        for (auto child : children) delete child;
    }
};

class TwoThreeTree {
private:
    Node23* root;

    // Recursive insert returning a pair: {promotedKey, newRightChild}
    pair<int, Node23*> insertRec(Node23* node, int k) {
        if (node->isLeaf) {
            node->keys.push_back(k);
            sort(node->keys.begin(), node->keys.end());

            if (node->keys.size() <= 2) {
                return {-1, nullptr};
            }

            // Leaf overflow: split into two nodes
            Node23* rightChild = new Node23(true);
            rightChild->keys.push_back(node->keys[2]);
            node->keys.pop_back();

            int promoted = node->keys[1];
            node->keys.pop_back();

            return {promoted, rightChild};
        } else {
            // Find child index
            int i = 0;
            while (i < (int)node->keys.size() && k > node->keys[i]) {
                i++;
            }

            auto res = insertRec(node->children[i], k);

            if (res.first != -1) {
                // Child split, insert promoted key and right child
                int promotedKey = res.first;
                Node23* rightChild = res.second;

                node->keys.insert(node->keys.begin() + i, promotedKey);
                node->children.insert(node->children.begin() + i + 1, rightChild);

                if (node->keys.size() <= 2) {
                    return {-1, nullptr};
                }

                // Internal node overflow: split node
                Node23* rightNode = new Node23(false);
                
                rightNode->keys.push_back(node->keys[2]);
                node->keys.pop_back();

                int promotedInternal = node->keys[1];
                node->keys.pop_back();

                if (!node->children.empty()) {
                    rightNode->children.push_back(node->children[2]);
                    rightNode->children.push_back(node->children[3]);
                    node->children.pop_back();
                    node->children.pop_back();
                }

                return {promotedInternal, rightNode};
            }
            return {-1, nullptr};
        }
    }

    void inorder(Node23* node) const {
        if (!node) return;
        size_t i = 0;
        for (; i < node->keys.size(); i++) {
            if (!node->isLeaf) inorder(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->isLeaf) inorder(node->children[i]);
    }

    void getMetrics(Node23* node, int& totalNodes, int& totalKeys) const {
        if (!node) return;
        totalNodes++;
        totalKeys += (int)node->keys.size();
        for (auto child : node->children) {
            getMetrics(child, totalNodes, totalKeys);
        }
    }

    int getHeight(Node23* node) const {
        if (!node || node->isLeaf) return 0;
        return 1 + getHeight(node->children[0]);
    }

    bool validateNode(Node23* node, int minKey, int maxKey, int expectedDepth, int currentDepth, string& err) const {
        if (!node) return true;
        if (node->keys.empty() || node->keys.size() > 2) {
            err = "Node contains invalid number of keys.";
            return false;
        }
        if (node->keys.size() == 2 && node->keys[0] >= node->keys[1]) {
            err = "Keys within node are not sorted.";
            return false;
        }
        for (int k : node->keys) {
            if (k <= minKey || k >= maxKey) {
                err = "Search-order constraint violated.";
                return false;
            }
        }
        if (node->isLeaf) {
            if (currentDepth != expectedDepth) {
                err = "Leaf nodes occur at different depths.";
                return false;
            }
            return true;
        }
        if (node->children.size() != node->keys.size() + 1) {
            err = "Number of children is inconsistent with number of keys.";
            return false;
        }

        if (!validateNode(node->children[0], minKey, node->keys[0], expectedDepth, currentDepth + 1, err)) return false;
        if (!validateNode(node->children[1], node->keys[0], node->keys.size() > 1 ? node->keys[1] : maxKey, expectedDepth, currentDepth + 1, err)) return false;
        if (node->keys.size() == 2) {
            if (!validateNode(node->children[2], node->keys[1], maxKey, expectedDepth, currentDepth + 1, err)) return false;
        }
        return true;
    }

public:
    TwoThreeTree() { root = new Node23(true); }
    ~TwoThreeTree() { delete root; }

    void insert(int k) {
        auto res = insertRec(root, k);
        if (res.first != -1) {
            Node23* newRoot = new Node23(false);
            newRoot->keys.push_back(res.first);
            newRoot->children.push_back(root);
            newRoot->children.push_back(res.second);
            root = newRoot;
        }
    }

    bool search(int k, int& comparisons) const {
        Node23* curr = root;
        while (curr) {
            size_t i = 0;
            while (i < curr->keys.size() && k > curr->keys[i]) {
                comparisons++;
                i++;
            }
            if (i < curr->keys.size() && k == curr->keys[i]) {
                comparisons++;
                return true;
            }
            comparisons++;
            if (curr->isLeaf) break;
            curr = curr->children[i];
        }
        return false;
    }

    void displayInorder() const {
        inorder(root);
        cout << endl;
    }

    void displayLevelOrder() const {
        if (!root) return;
        queue<pair<Node23*, int>> q;
        q.push(make_pair(root, 0));
        int lastLevel = -1;

        while (!q.empty()) {
            pair<Node23*, int> p = q.front();
            q.pop();
            Node23* curr = p.first;
            int level = p.second;

            if (curr->keys.empty()) continue;

            if (level != lastLevel) {
                if (lastLevel != -1) cout << endl;
                cout << "Level " << level << ": [";
                for (size_t i = 0; i < curr->keys.size(); i++) {
                    cout << curr->keys[i] << (i + 1 < curr->keys.size() ? ", " : "");
                }
                cout << "] ";
                lastLevel = level;
            } else {
                cout << "[";
                for (size_t i = 0; i < curr->keys.size(); i++) {
                    cout << curr->keys[i] << (i + 1 < curr->keys.size() ? ", " : "");
                }
                cout << "] ";
            }

            for (auto child : curr->children) {
                if (child && !child->keys.empty()) {
                    q.push(make_pair(child, level + 1));
                }
            }
        }
        cout << endl;
    }

    int getTotalNodes() const {
        int nodes = 0, keys = 0;
        getMetrics(root, nodes, keys);
        return nodes;
    }

    int getTotalKeys() const {
        int nodes = 0, keys = 0;
        getMetrics(root, nodes, keys);
        return keys;
    }

    int getHeight() const {
        return getHeight(root);
    }

    bool validate(string& err) const {
        if (!root) return true;
        int expectedDepth = 0;
        Node23* curr = root;
        while (!curr->isLeaf && !curr->children.empty()) {
            expectedDepth++;
            curr = curr->children[0];
        }
        return validateNode(root, -2e9, 2e9, expectedDepth, 0, err);
    }
};

// ==========================================
// PART C: AVL TREE IMPLEMENTATION
// ==========================================

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* n) const { return n ? n->height : 0; }
    int getBalance(AVLNode* n) const { return n ? height(n->left) - height(n->right) : 0; }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insertNode(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if (key < node->key) node->left = insertNode(node->left, key);
        else if (key > node->key) node->right = insertNode(node->right, key);
        else return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) return rightRotate(node);
        if (balance < -1 && key > node->right->key) return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void destroy(AVLNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(int key) { root = insertNode(root, key); }

    bool search(int key, int& comparisons) const {
        AVLNode* curr = root;
        while (curr) {
            comparisons++;
            if (key == curr->key) return true;
            else if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    int getHeight() const { return height(root); }
};

// ==========================================
// PART E: RECORD MANAGEMENT APPLICATION
// ==========================================

struct Record {
    int id;
    string name;
};

int main() {
    cout << "===========================================\n";
    cout << "TASK 1 & 2: 2-3 TREE DEMO & VALIDATION\n";
    cout << "===========================================\n";

    TwoThreeTree tree;
    vector<int> seq = {30, 10, 20, 40, 50};
    string err;

    for (int k : seq) {
        tree.insert(k);
        bool isValid = tree.validate(err);
        cout << "Inserted " << k << " -> Validation: " << (isValid ? "PASSED" : "FAILED (" + err + ")") << endl;
    }

    cout << "\nLevel-wise Structure:\n";
    tree.displayLevelOrder();
    cout << "Total Nodes: " << tree.getTotalNodes() << endl;
    cout << "Total Keys: " << tree.getTotalKeys() << endl;
    cout << "Height: " << tree.getHeight() << endl;

    int comps = 0;
    cout << "Search 30: " << (tree.search(30, comps) ? "Found" : "Not Found") << " (Comparisons: " << comps << ")\n\n";

    cout << "===========================================\n";
    cout << "TASK 5: INTEGRATED RECORD MANAGEMENT\n";
    cout << "===========================================\n";

    vector<Record> records = {
        {101, "Aarav Sharma"}, {105, "Priya Nair"}, {102, "Rohan Verma"},
        {108, "Neha Singh"}, {103, "Kabir Mehta"}, {110, "Ananya Roy"},
        {104, "Dev Patel"}, {107, "Sneha Joshi"}, {106, "Karan Malhotra"}, {109, "Tanvi Kapoor"}
    };

    TwoThreeTree recordTree;
    for (auto& r : records) {
        recordTree.insert(r.id);
        cout << "[+] Added Record ID: " << r.id << " -> " << r.name << endl;
    }

    if (recordTree.validate(err)) {
        cout << "\nTree Validation after 10 insertions: PASSED\n";
    }

    cout << "\nSorted Record IDs via Inorder Traversal:\n";
    recordTree.displayInorder();
    cout << endl;

    return 0;
}