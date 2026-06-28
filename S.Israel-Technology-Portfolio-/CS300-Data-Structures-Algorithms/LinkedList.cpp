//============================================================================
// Name        : LinkedList.cpp
// Author      : Stephen Israel
// Course      : CS 300
// Assignment  : Module Three - Linked List
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 3-2 Lists and Searching
//============================================================================

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;

    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a singly linked list.
 */
class LinkedList {

private:
    /**
     * Internal structure for each linked list node.
     * Each node stores one Bid and a pointer to the next node.
     */
    struct Node {
        Bid bid;
        Node* next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // Initialize housekeeping variables for an empty list.
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // Start at the head.
    Node* current = head;
    Node* temp;

    // Loop over each node, detach from list, then delete.
    while (current != nullptr) {
        temp = current;          // hang on to current node
        current = current->next; // make current the next node
        delete temp;             // delete the orphan node
    }

    // Reset housekeeping variables after deleting all nodes.
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // Create a new node to store the bid.
    Node* newNode = new Node(bid);

    // If the list is empty, the new node is both the head and tail.
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        // Link the current tail to the new node, then update the tail.
        tail->next = newNode;
        tail = newNode;
    }

    // Increase the number of nodes in the list.
    size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // Create a new node to store the bid.
    Node* newNode = new Node(bid);

    // If the list is empty, the new node is both the head and tail.
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        // Point the new node to the current head, then update head.
        newNode->next = head;
        head = newNode;
    }

    // Increase the number of nodes in the list.
    size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // Start at the head of the list.
    Node* current = head;

    // Loop through each node and display its bid information.
    while (current != nullptr) {
        cout << current->bid.bidId << ": "
             << current->bid.title << " | "
             << current->bid.amount << " | "
             << current->bid.fund << endl;

        current = current->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // If the list is empty, there is nothing to remove.
    if (head == nullptr) {
        return;
    }

    // Special case: the matching node is the head.
    if (head->bid.bidId == bidId) {
        Node* temp = head;
        head = head->next;

        // If the list had only one node, update tail as well.
        if (temp == tail) {
            tail = nullptr;
        }

        delete temp;
        size--;
        return;
    }

    // Start at the head and look ahead to find the matching node.
    Node* current = head;

    while (current->next != nullptr) {
        // If the next node matches, remove it from the list.
        if (current->next->bid.bidId == bidId) {
            Node* temp = current->next;

            // Bypass the node being removed.
            current->next = temp->next;

            // If removing the tail, update tail to the current node.
            if (temp == tail) {
                tail = current;
            }

            delete temp;
            size--;
            return;
        }

        current = current->next;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // Start at the head of the list.
    Node* current = head;

    // Traverse the list until the bid is found or the end is reached.
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            return current->bid;
        }

        current = current->next;
    }

    // Return an empty bid if no match is found.
    Bid bid;
    return bid;
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    getline(cin, bid.fund);

    cout << "Enter amount: ";
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList* list) {
    cout << "Loading CSV file " << csvPath << endl;

    // Initialize the CSV Parser.
    csv::Parser file = csv::Parser(csvPath);

    try {
        // Loop to read rows of a CSV file.
        for (int i = 0; i < file.rowCount(); i++) {

            // Initialize a bid using data from current row.
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // Add this bid to the end of the linked list.
            list->Append(bid);
        }
    }
    catch (csv::Error& e) {
        cerr << e.what() << endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted characters.
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    str.erase(remove(str.begin(), str.end(), ','), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // Process command line arguments.
    string csvPath;
    string bidKey;

    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;

    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;

    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;
    Bid bid;

    int choice = 0;

    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);
            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 3:
            bidList.PrintList();
            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 5:
            bidList.Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
