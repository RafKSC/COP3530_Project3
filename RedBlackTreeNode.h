#pragma once
#include "Vehicle.h"
#include <string>
#include <vector>

struct RBNode {
public:
    Vehicle data;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    bool isRed;  // true for red, false for black

    RBNode(const Vehicle& vehicle) {
        this->data = vehicle;
        this->parent = nullptr;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->isRed = true;
    }
};

class RBTree {
private:
    RBNode* root;
    RBNode* nil;
public:
    RBTree();
    ~RBTree();
    void deleteChildrenTrees(RBNode* node);
    void deleteNode(const string& vin);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node);
    void fixDeletion(RBNode* x);
    void insert(const Vehicle& vehicle);
    Vehicle* search(const std::string& vin);
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);
    void fixInsertion(RBNode* k);
    void exportToCSV(const string& filename, const vector<Vehicle>& vehicles);
    vector<Vehicle> searchByAttribute(const string& attribute, const string& value);
    void searchByAttributeHelper(RBNode* node, const string& attribute, const string& value, vector<Vehicle>& result);

};
