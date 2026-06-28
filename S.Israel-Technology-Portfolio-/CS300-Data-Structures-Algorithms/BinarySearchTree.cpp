//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Stephen Israel
// Version     : 1.0
// Copyright   : Copyright (c) 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Forward declarations
double strToDouble(string str, char ch);
void displayBid(struct Bid bid);

// Define a structure to hold bid information
struct Bid {
    string bidId; // Unique identifier
    string title;
    string fund;
    double amount;

    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize node with a bid
    Node(Bid aBid) : Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to implement a binary
 * search tree. Each node stores one bid and is organized by bid ID.
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor initializes the root pointer to nullptr so the tree starts
 * empty and can safely accept the first inserted bid.
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor releases dynamically allocated nodes from memory.
 */
BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

/**
 * Recursively deletes all nodes in the tree using post-order traversal.
 */
void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

/**
 * Traverse the tree in order.
 */
void BinarySearchTree::InOrder() {
    inOrder(root);
}

/**
 * Traverse the tree in post-order.
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);
}

/**
 * Traverse the tree in pre-order.
 */
void BinarySearchTree::PreOrder() {
    preOrder(root);
}

/**
 * Insert a bid into the binary search tree.
 */
void BinarySearchTree::Insert(Bid bid) {
    // If the tree is empty, the new bid becomes the root node.
    if (root == nullptr) {
        root = new Node(bid);
    }
    else {
        addNode(root, bid);
    }
}

/**
 * Remove a bid from the binary search tree.
 */
void BinarySearchTree::Remove(string bidId) {
    root = removeNode(root, bidId);
}

/**
 * Search for a bid by bid ID.
 */
Bid BinarySearchTree::Search(string bidId) {
    Node* current = root;

    // Move down the tree until the bid is found or the bottom is reached.
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            return current->bid;
        }
        else if (bidId < current->bid.bidId) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // Return an empty bid if the bid ID was not found.
    Bid bid;
    return bid;
}

/**
 * Add a bid to a node recursively.
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // Smaller bid IDs go to the left subtree.
    if (bid.bidId < node->bid.bidId) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else {
            addNode(node->left, bid);
        }
    }
    // Larger or equal bid IDs go to the right subtree.
    else {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else {
            addNode(node->right, bid);
        }
    }
}

/**
 * In-order traversal displays bids from the smallest bid ID to the largest.
 */
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        displayBid(node->bid);
        inOrder(node->right);
    }
}

/**
 * Post-order traversal visits left subtree, right subtree, then current node.
 */
void BinarySearchTree::postOrder(Node* node) {
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        displayBid(node->bid);
    }
}

/**
 * Pre-order traversal visits current node, left subtree, then right subtree.
 */
void BinarySearchTree::preOrder(Node* node) {
    if (node != nullptr) {
        displayBid(node->bid);
        preOrder(node->left);
        preOrder(node->right);
    }
}

/**
 * Remove a bid from a node recursively.
 *
 * @param node Current node in tree
 * @param bidId Bid ID to remove
 * @return Updated node pointer after removal
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) {
        return node;
    }

    // Search the left subtree if the bid ID is smaller.
    if (bidId < node->bid.bidId) {
        node->left = removeNode(node->left, bidId);
    }
    // Search the right subtree if the bid ID is larger.
    else if (bidId > node->bid.bidId) {
        node->right = removeNode(node->right, bidId);
    }
    // Matching node found.
    else {
        // Case 1 and 2: node has no left child or only a right child.
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        // Case 2: node has only a left child.
        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: node has two children.
        // Find the smallest node in the right subtree to replace this node.
        Node* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        node->bid = temp->bid;
        node->right = removeNode(node->right, temp->bid.bidId);
    }

    return node;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console.
 *
 * @param bid Struct containing the bid information
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
}

/**
 * Load a CSV file containing bids into the binary search tree.
 *
 * @param csvPath The path to the CSV file to load
 * @param bst Pointer to the binary search tree that stores the bids
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // Initialize the CSV Parser using the given path.
    csv::Parser file = csv::Parser(csvPath);

    // Read and display header row.
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // Loop to read rows of a CSV file.
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a bid structure and populate it with CSV values.
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // Insert this bid into the binary search tree.
            bst->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        cerr << e.what() << endl;
    }
}

/**
 * Simple C function to convert a string to a double after stripping out an
 * unwanted character.
 *
 * Credit: http://stackoverflow.com/a/24875936
 *
 * @param str String to convert
 * @param ch Character to strip out
 * @return Converted double value
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method.
 */
int main(int argc, char* argv[]) {

    // Process command line arguments.
    string csvPath;
    string bidKey;

    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable.
    clock_t ticks;

    // Define a binary search tree to hold all bids.
    BinarySearchTree* bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ticks = clock();

            loadBids(csvPath, bst);

            ticks = clock() - ticks;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks;

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bst->Remove(bidKey);
            break;

        case 9:
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

    delete bst;
    return 0;
}
