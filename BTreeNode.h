#include <vector>
#include "Vehicle.h"

using namespace std;

struct BTreeNode {
    vector<Vehicle> keys;
    vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool leaf);
    BTreeNode(Vehicle key, bool leaf);

    int findKey(const Vehicle& key);
};

class BTree {
private:
    BTreeNode* root;  // Root node of the tree
    void insertNonFull(BTreeNode* node, const Vehicle& key);
    void splitNode(BTreeNode* parent, int i);
    Vehicle* searchHelper(BTreeNode* node, const string& vin);
    void searchByAttributeHelper(BTreeNode* node, const string& attribute, const string& value, vector<Vehicle>& result);
    void deleteHelper(BTreeNode* node, const string& key);

public:
    // Constructor
    BTree();

    void insert(const Vehicle& key);
    Vehicle* search(const string& vin);
    vector<Vehicle> searchByAttribute(const string& attribute, const string& value);
    void deleteKey(const string& key);
};
