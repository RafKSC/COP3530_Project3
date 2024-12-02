// RedBlackTreeNode.cpp
#include "RedBlackTreeNode.h"
#include <iostream>
#include <fstream>

RBTree::RBTree() {
    nil = new RBNode(Vehicle());
    nil->isRed = false;  // nil should always be black
    root = nil;
}

void RBTree::deleteChildrenTrees(RBNode* node) {
    if (node == nullptr || node == nil)
        return;

    deleteChildrenTrees(node->left);
    deleteChildrenTrees(node->right);
    delete node;
}

RBTree::~RBTree() {
    if (root != nil)
        deleteChildrenTrees(root);
    delete nil;
    root = nullptr;
    nil = nullptr;
}

void RBTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotate(RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;

    if (y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;

    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBTree::insert(const Vehicle& vehicle) {
    RBNode* node = new RBNode(vehicle);
    node->left = nil;
    node->right = nil;
    node->parent = nil;

    RBNode* y = nil;
    RBNode* x = root;

    while (x != nil) {
        y = x;
        if (node->data.getVin() < x->data.getVin())
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y == nil)
        root = node;
    else if (node->data.getVin() < y->data.getVin())
        y->left = node;
    else
        y->right = node;
    fixInsertion(node);
}

void RBTree::fixInsertion(RBNode* k) {
    while (k->parent->isRed) {
        if (k->parent == k->parent->parent->left) {
            RBNode* y = k->parent->parent->right;

            if (y->isRed) {
                k->parent->isRed = false;
                y->isRed = false;
                k->parent->parent->isRed = true;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->isRed = false;
                k->parent->parent->isRed = true;
                rightRotate(k->parent->parent);
            }
        }
        else {
            RBNode* y = k->parent->parent->left;

            if (y->isRed) {
                k->parent->isRed = false;
                y->isRed = false;
                k->parent->parent->isRed = true;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->isRed = false;
                k->parent->parent->isRed = true;
                leftRotate(k->parent->parent);
            }
        }
        if (k == root)
            break;
    }
    root->isRed = false;
}

Vehicle* RBTree::search(const string& vin) {
    RBNode* node = root;
    while (node != nil) {
        if (vin == node->data.getVin())
            return &(node->data);
        if (vin < node->data.getVin())
            node = node->left;
        else
            node = node->right;
    }
    return nullptr;
}

void RBTree::searchByAttributeHelper(RBNode* node, const string& attribute, const string& value, vector<Vehicle>& result) {
    if (node == nil)
        return;
    // Left
    searchByAttributeHelper(node->left, attribute, value, result);

    // Node
    bool matches = false;
    if (attribute == "make")
        matches = node->data.getMake() == value;
    else if (attribute == "model")
        matches = node->data.getModel() == value;
    else if (attribute == "year")
        matches = to_string(node->data.getModelYear()) == value;
    else if (attribute == "type")
        matches = node->data.getEvType() == value;
    if (matches)
        result.push_back(node->data);

    // Right
    searchByAttributeHelper(node->right, attribute, value, result);
}

vector<Vehicle> RBTree::searchByAttribute(const string& attribute, const string& value) {
    vector<Vehicle> result;
    searchByAttributeHelper(root, attribute, value, result);
    return result;
}

void RBTree::exportToCSV(const string& filename, const vector<Vehicle>& vehicles) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open output file: " << filename << endl;
        return;
    }

    file << "VIN,County,City,State,PostalCode,ModelYear,Make,Model,EvType,"
         << "CafvEligible,ElectricRange,BaseMsrp,LegislativeDistrict,"
         << "DolVehicleId,VehicleLocation,ElectricUtility,CensusTract\n";

    for (const auto& vehicle : vehicles) {
        file << vehicle.getVin() << ","
             << vehicle.getCounty() << ","
             << vehicle.getCity() << ","
             << vehicle.getState() << ","
             << vehicle.getPostalCode() << ","
             << vehicle.getModelYear() << ","
             << vehicle.getMake() << ","
             << vehicle.getModel() << ","
             << vehicle.getEvType() << ","
             << (vehicle.isCafvEligible() ? "Yes" : "No") << ","
             << vehicle.getElectricRange() << ","
             << vehicle.getBaseMsrp() << ","
             << vehicle.getLegislativeDistrict() << ","
             << vehicle.getDolVehicleId() << ","
             << vehicle.getVehicleLocation() << ","
             << vehicle.getElectricUtility() << ","
             << vehicle.getCensusTract() << "\n";
    }
    file.close();
}

void RBTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

RBNode* RBTree::minimum(RBNode* node) {
    while (node->left != nil)
        node = node->left;
    return node;
}

void RBTree::deleteNode(const string& vin) {
    RBNode* z = root;
    // Find the node to delete
    while (z != nil) {
        if (vin == z->data.getVin())
            break;
        if (vin < z->data.getVin())
            z = z->left;
        else
            z = z->right;
    }
    if (z == nil) {
        cout << "VIN not found in tree" << endl;
        return;
    }

    RBNode* y = z;
    RBNode* x;
    bool y_original_color = y->isRed;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->isRed;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->isRed = z->isRed;
    }

    delete z;

    if (!y_original_color)
        fixDeletion(x);
}

void RBTree::fixDeletion(RBNode* x) {
    while (x != root && !x->isRed) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;

            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if (!w->left->isRed && !w->right->isRed) {
                w->isRed = true;
                x = x->parent;
            }
            else {
                if (!w->right->isRed) {
                    w->left->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = x->parent->right;
                }

                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->right->isRed = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
            RBNode* w = x->parent->left;

            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if (!w->right->isRed && !w->left->isRed) {
                w->isRed = true;
                x = x->parent;
            }
            else {
                if (!w->left->isRed) {
                    w->right->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = x->parent->left;
                }

                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->isRed = false;
}