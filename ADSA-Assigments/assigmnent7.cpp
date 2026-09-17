#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// ==========================================
// ARBITRARY TREE
// ==========================================
struct TreeNode {
    int key;
    vector<TreeNode*> children;

    TreeNode(int val) {
        key = val;
    }
};

class ArbitraryTree {
public:
    TreeNode* root;
    map<int, TreeNode*> nodeMap;

    ArbitraryTree() {
        root = NULL;
    }

    TreeNode* createNode(int key) {
        if (nodeMap.find(key) == nodeMap.end()) {
            TreeNode* newNode = new TreeNode(key);
            nodeMap[key] = newNode;
            if (root == NULL) root = newNode;
        }
        return nodeMap[key];
    }

    void addChild(int parentKey, int childKey) {
        TreeNode* parent = createNode(parentKey);
        TreeNode* child = createNode(childKey);
        parent->children.push_back(child);
    }

    void dfs(TreeNode* node) {
        if (!node) return;
        cout << node->key << " ";
        for (size_t i = 0; i < node->children.size(); i++) {
            dfs(node->children[i]);
        }
    }

    void bfs() {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            cout << curr->key << " ";

            for (size_t i = 0; i < curr->children.size(); i++) {
                q.push(curr->children[i]);
            }
        }
    }

    int getHeight(TreeNode* node = NULL) {
        if (node == NULL) node = root;
        if (!node || node->children.empty()) return 0;

        int maxHeight = 0;
        for (size_t i = 0; i < node->children.size(); i++) {
            maxHeight = max(maxHeight, getHeight(node->children[i]));
        }
        return 1 + maxHeight;
    }

    void printChildrenCount() {
        for (map<int, TreeNode*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
            cout << "Node " << it->first << ": " << it->second->children.size() << " children\n";
        }
    }

    void printLeafNodes() {
        cout << "Leaf Nodes: ";
        for (map<int, TreeNode*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
            if (it->second->children.empty()) {
                cout << it->first << " ";
            }
        }
        cout << "\n";
    }

    int getMaxDegree() {
        int maxDegree = 0;
        for (map<int, TreeNode*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
            maxDegree = max(maxDegree, (int)it->second->children.size());
        }
        return maxDegree;
    }

    // Clean ASCII tree drawing (prevents terminal symbol errors)
    void printTree(TreeNode* node = NULL, string indent = "") {
        if (node == NULL) {
            node = root;
            if (!node) return;
            cout << node->key << "\n";
        }

        for (size_t i = 0; i < node->children.size(); i++) {
            cout << indent << "+-- " << node->children[i]->key << "\n";
            printTree(node->children[i], indent + "|   ");
        }
    }
};

// ==========================================
// B-TREE
// ==========================================
struct BTreeNode {
    int t;
    bool isLeaf;
    vector<int> keys;
    vector<BTreeNode*> children;

    BTreeNode(int degree, bool leaf) {
        t = degree;
        isLeaf = leaf;
    }
};

class BTree {
public:
    BTreeNode* root;
    int t;

    BTree(int degree) {
        t = degree;
        root = new BTreeNode(t, true);
    }

    void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
        BTreeNode* newNode = new BTreeNode(child->t, child->isLeaf);

        for (int j = 0; j < t - 1; j++) {
            newNode->keys.push_back(child->keys[j + t]);
        }

        if (!child->isLeaf) {
            for (int j = 0; j < t; j++) {
                newNode->children.push_back(child->children[j + t]);
            }
        }

        child->keys.resize(t - 1);
        if (!child->isLeaf) child->children.resize(t);

        parent->children.insert(parent->children.begin() + i + 1, newNode);
        parent->keys.insert(parent->keys.begin() + i, child->keys[t - 1]);
    }

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->keys.size() - 1;

        if (node->isLeaf) {
            node->keys.push_back(0);
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < node->keys[i]) i--;
            i++;

            if ((int)node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], key);
        }
    }

    void insert(int key) {
        if ((int)root->keys.size() == 2 * t - 1) {
            BTreeNode* newRoot = new BTreeNode(t, false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);

            int i = 0;
            if (newRoot->keys[0] < key) i++;
            insertNonFull(newRoot->children[i], key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }

    bool search(BTreeNode* node, int key) {
        size_t i = 0;
        while (i < node->keys.size() && key > node->keys[i]) i++;

        if (i < node->keys.size() && node->keys[i] == key) return true;
        if (node->isLeaf) return false;

        return search(node->children[i], key);
    }

    void printLevelWise() {
        if (!root) return;

        queue<pair<BTreeNode*, int> > q;
        q.push(make_pair(root, 0));
        int currentLevel = 0;

        cout << "Level 0: ";
        while (!q.empty()) {
            pair<BTreeNode*, int> current = q.front();
            q.pop();

            BTreeNode* node = current.first;
            int level = current.second;

            if (level > currentLevel) {
                cout << "\nLevel " << level << ": ";
                currentLevel = level;
            }

            cout << "[";
            for (size_t i = 0; i < node->keys.size(); i++) {
                cout << node->keys[i] << (i + 1 < node->keys.size() ? " " : "");
            }
            cout << "] ";

            if (!node->isLeaf) {
                for (size_t i = 0; i < node->children.size(); i++) {
                    q.push(make_pair(node->children[i], level + 1));
                }
            }
        }
        cout << "\n";
    }

    void countStats(BTreeNode* node, int& totalNodes, int& totalKeys) {
        if (!node) return;
        totalNodes++;
        totalKeys += node->keys.size();

        if (!node->isLeaf) {
            for (size_t i = 0; i < node->children.size(); i++) {
                countStats(node->children[i], totalNodes, totalKeys);
            }
        }
    }

    int getHeight(BTreeNode* node = NULL) {
        if (node == NULL) node = root;
        if (!node) return 0;
        if (node->isLeaf) return 1;
        return 1 + getHeight(node->children[0]);
    }
};

// ==========================================
// DRIVER CODE
// ==========================================
void runTask1() {
    cout << "==========================================\n";
    cout << "TASK 1: PROGRAMMATIC ARBITRARY TREE\n";
    cout << "==========================================\n";

    ArbitraryTree tree;
    tree.addChild(1, 2);
    tree.addChild(1, 3);
    tree.addChild(1, 4);
    tree.addChild(2, 5);
    tree.addChild(2, 6);
    tree.addChild(2, 7);
    tree.addChild(6, 9);
    tree.addChild(4, 8);

    cout << "Tree Structure:\n";
    tree.printTree();

    cout << "\nDFS Traversal: ";
    tree.dfs(tree.root);

    cout << "\nBFS Traversal: ";
    tree.bfs();

    cout << "\n\nHeight: " << tree.getHeight();
    cout << "\nTotal Nodes: " << tree.nodeMap.size() << "\n\n";

    tree.printChildrenCount();
    tree.printLeafNodes();
}

void runTask2() {
    cout << "\n==========================================\n";
    cout << "TASK 2: INPUT-DRIVEN ARBITRARY TREE DEMO\n";
    cout << "==========================================\n";

    ArbitraryTree tree;
    tree.addChild(1, 2);
    tree.addChild(1, 3);
    tree.addChild(1, 4);
    tree.addChild(2, 5);
    tree.addChild(2, 6);
    tree.addChild(4, 7);
    tree.addChild(4, 8);

    cout << "Tree Structure:\n";
    tree.printTree();

    cout << "\nDFS Traversal: ";
    tree.dfs(tree.root);

    cout << "\nBFS Traversal: ";
    tree.bfs();

    cout << "\n\nHeight: " << tree.getHeight();
    cout << "\nMax Degree: " << tree.getMaxDegree() << "\n";
    tree.printLeafNodes();
}

void runTask3() {
    cout << "\n==========================================\n";
    cout << "TASK 3: B-TREE WITH t = 3\n";
    cout << "==========================================\n";

    BTree btree(3);
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};

    for (int i = 0; i < 8; i++) {
        btree.insert(keys[i]);
    }

    cout << "B-Tree Level-Wise Structure:\n";
    btree.printLevelWise();

    int totalNodes = 0, totalKeys = 0;
    btree.countStats(btree.root, totalNodes, totalKeys);

    cout << "\nTotal Nodes: " << totalNodes;
    cout << "\nTotal Keys: " << totalKeys << "\n";

    cout << "\nSearch 17: " << (btree.search(btree.root, 17) ? "Found" : "Not Found");
    cout << "\nSearch 25: " << (btree.search(btree.root, 25) ? "Found" : "Not Found") << "\n";
}

void runTask4() {
    cout << "\n==========================================\n";
    cout << "TASK 4: B-TREE WITH 10,000 KEYS\n";
    cout << "==========================================\n";

    mt19937 gen(42);
    uniform_int_distribution<int> dist(1, 100000);

    vector<int> keys10k;
    while (keys10k.size() < 10000) {
        keys10k.push_back(dist(gen));
    }

    int degrees[] = {2, 3, 5, 10};

    for (int d = 0; d < 4; d++) {
        int t = degrees[d];
        BTree btree(t);

        auto start = chrono::high_resolution_clock::now();
        for (size_t i = 0; i < keys10k.size(); i++) {
            btree.insert(keys10k[i]);
        }
        auto stop = chrono::high_resolution_clock::now();

        double duration = chrono::duration_cast<chrono::microseconds>(stop - start).count() / 1000.0;

        int totalNodes = 0, totalKeys = 0;
        btree.countStats(btree.root, totalNodes, totalKeys);

        cout << "\n--- Degree t = " << t << " ---\n";
        cout << "Nodes      : " << totalNodes << "\n";
        cout << "Keys       : " << totalKeys << "\n";
        cout << "Height     : " << btree.getHeight() << "\n";
        cout << "Time Taken : " << duration << " ms\n";
    }
}

int main() {
    runTask1();
    runTask2();
    runTask3();
    runTask4();
    return 0;
}