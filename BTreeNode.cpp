#include "BTreeNode.h"
#include <iostream>

using namespace std;

BTreeNode::BTreeNode(bool leaf) {
    isLeaf = leaf;
}

BTreeNode::BTreeNode(Vehicle key, bool leaf) {
    isLeaf = leaf;
    keys.push_back(key);
}

BTree::BTree()
{
    root = nullptr;
}

int BTreeNode::findKey(const Vehicle& key) {
    int i = 0;
    while (i < keys.size() && keys[i].getVin() < key.getVin()) {
        i++;
    }
    return i;
}

// Insert key into the B-tree
void BTree::insert(const Vehicle& key) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(key);
    }
    else {
        if (root->keys.size() == 2 * 3 - 1) {
            // create a new root
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitNode(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
}

// Helper function to insert into a non-full node
void BTree::insertNonFull(BTreeNode* node, const Vehicle& key) {
    int i = node->keys.size() - 1;

    // If the node is a leaf
    if (node->isLeaf) {
        while (i > 0 && node->keys[i].getVin() > key.getVin()) {
            i--;
        }
        // Ensure the index is valid for insertion
        if (i + 1 >= 0 && i + 1 <= node->keys.size()) {
            node->keys.insert(node->keys.begin() + i + 1, key);
        }
        else {
            cout << "Error: Out of Bounds" << endl;
        }
    }
    else {
        while (i >= 0 && node->keys[i].getVin() > key.getVin()) {
            i--;
        }
        i++;

        if (node->children[i]->keys.size() == 2 * 3 - 1) {
            splitNode(node, i);
            if (key.getVin() > node->keys[i].getVin()) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void BTree::splitNode(BTreeNode* parent, int i) {
    BTreeNode* fullChild = parent->children[i];
    BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);

    int middleIndex = 3 - 1; // Middle index in the full node (degree 3)
    Vehicle middleKey = fullChild->keys[middleIndex];

    for (int j = middleIndex + 1; j < 2 * 3 - 1; j++) {
        newChild->keys.push_back(fullChild->keys[j]);
    }
    fullChild->keys.resize(middleIndex);

    if (!fullChild->isLeaf) {
        for (int j = 3; j < 2 * 3; j++) {
            newChild->children.push_back(fullChild->children[j]);
        }
        fullChild->children.resize(3);
    }
    parent->keys.insert(parent->keys.begin() + i, middleKey);
    parent->children.insert(parent->children.begin() + i + 1, newChild);
}

Vehicle* BTree::searchHelper(BTreeNode* node, const string& vin) {
    if (node == nullptr) {
        return nullptr;
    }

    int i = 0;
    while (i < node->keys.size() && vin > node->keys[i].getVin()) {
        i++;
    }

    if (i < node->keys.size() && vin == node->keys[i].getVin()) {
        return &node->keys[i];
    }

    if (node->isLeaf) {
        return nullptr;
    }
    return searchHelper(node->children[i], vin);
}

Vehicle* BTree::search(const std::string& vin) {
    return searchHelper(root, vin);
}

void BTree::searchByAttributeHelper(BTreeNode* node, const std::string& attribute, const std::string& value, std::vector<Vehicle>& result) {
    if (node == nullptr) return;

    for (auto& vehicle : node->keys) {
        bool matches = false;
        if (attribute == "make") matches = vehicle.getMake() == value;
        else if (attribute == "model") matches = vehicle.getModel() == value;
        else if (attribute == "year") matches = std::to_string(vehicle.getModelYear()) == value;
        else if (attribute == "type") matches = vehicle.getEvType() == value;

        if (matches) result.push_back(vehicle);
    }
    if (!node->isLeaf) {
        for (auto& child : node->children) {
            searchByAttributeHelper(child, attribute, value, result);
        }
    }
}

vector<Vehicle> BTree::searchByAttribute(const std::string& attribute, const std::string& value) {
    std::vector<Vehicle> result;
    searchByAttributeHelper(root, attribute, value, result);
    return result;
}

void BTree::deleteHelper(BTreeNode* node, const string& vin) {
    int i = 0;

    while (i < node->keys.size() && vin > node->keys[i].getVin()) {
        i++;
    }

    // If the key is found in this node
    if (i < node->keys.size() && vin == node->keys[i].getVin()) {
        node->keys.erase(node->keys.begin() + i);
        return;
    }
    else if (!node->isLeaf) {
        // If the key is not found in this node, continue traversal
        for (auto& child : node->children) {
            deleteHelper(child, vin);
        }
    }
}

// Public function to delete a key from the B-tree
void BTree::deleteKey(const string& vin) {
    deleteHelper(root, vin);
}
