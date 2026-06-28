// Corner Grocer - Item Tracking Program
// Author: Stephen Israel
// Purpose: Reads a text file of grocery items, counts how many times
// each item appears, and allows the user to look up or display results.

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// This class manages all grocery tracking functions
class GroceryTracker {
public:
    // Constructor - takes the name of the input file
    explicit GroceryTracker(const string& inputPath) : inputFilePath(inputPath) {}

    // Reads the input file and builds a map of item frequencies
    bool LoadData() {
        ifstream inFS(inputFilePath);
        if (!inFS.is_open()) {
            cerr << "Error: Could not open input file: " << inputFilePath << endl;
            return false;
        }

        string item;
        while (inFS >> item) {
            Normalize(item);          // make item lowercase for consistency
            if (!item.empty()) {
                ++freq[item];         // count each item
            }
        }
        inFS.close();

        // Write data to backup file
        return WriteBackup("frequency.dat");
    }

    // Finds the frequency of a specific item
    int GetFrequency(const string& itemRaw) const {
        string key = itemRaw;
        NormalizeConst(key);
        auto it = freq.find(key);
        return (it != freq.end()) ? it->second : 0;   // return 0 if not found
    }

    // Prints all items and their counts
    void PrintAllFrequencies() const {
        if (freq.empty()) {
            cout << "No items found." << endl;
            return;
        }
        for (const auto& kv : freq) {
            cout << kv.first << " " << kv.second << endl;
        }
    }

    // Prints a histogram showing frequency with asterisks
    void PrintHistogram(char symbol = '*') const {
        if (freq.empty()) {
            cout << "No items found." << endl;
            return;
        }

        // Find the longest item name for clean spacing
        size_t widest = 0;
        for (const auto& kv : freq) widest = max(widest, kv.first.size());

        // Print each item followed by that many stars
        for (const auto& kv : freq) {
            cout << left << setw(static_cast<int>(widest) + 1) << kv.first << " ";
            for (int i = 0; i < kv.second; ++i) cout << symbol;
            cout << endl;
        }
    }

private:
    string inputFilePath;
    map<string, int> freq;  // holds item name and frequency

    // Saves data to a backup file called frequency.dat
    bool WriteBackup(const string& outPath) const {
        ofstream outFS(outPath);
        if (!outFS.is_open()) {
            cerr << "Error: Could not write to " << outPath << endl;
            return false;
        }
        for (const auto& kv : freq) {
            outFS << kv.first << " " << kv.second << "\n";
        }
        outFS.close();
        return true;
    }

    // Converts all letters in a word to lowercase
    static void Normalize(string& s) {
        for (char& c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    static void NormalizeConst(string& s) { Normalize(s); }
};

// Displays the menu and validates user input
int GetMenuChoice() {
    cout << "\n===== Corner Grocer Menu =====\n";
    cout << "1. Look up frequency for a specific item\n";
    cout << "2. Print frequency list for all items\n";
    cout << "3. Print histogram of all items\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";

    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 4) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
            return choice;
        }
        cout << "Invalid input. Enter a number between 1 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Asks the user to type an item name
string PromptItem() {
    cout << "Enter item name: ";
    string s;
    getline(cin, s);

    // Remove extra spaces at beginning or end
    while (!s.empty() && isspace(static_cast<unsigned char>(s.front()))) s.erase(s.begin());
    while (!s.empty() && isspace(static_cast<unsigned char>(s.back()))) s.pop_back();
    return s;
}

// Main function
int main() {
    const string INPUT_FILE = "CS210_Project_Three_Input_File.txt";

    GroceryTracker tracker(INPUT_FILE);

    // Load the data from file
    if (!tracker.LoadData()) {
        cout << "Program cannot continue without input data. Exiting.\n";
        return 1;
    }

    // Keep showing the menu until the user exits
    while (true) {
        int choice = GetMenuChoice();

        if (choice == 1) {
            // Option 1: look up a specific item
            string item = PromptItem();
            int count = tracker.GetFrequency(item);
            cout << item << " " << count << endl;
        }
        else if (choice == 2) {
            // Option 2: print all items and their frequencies
            tracker.PrintAllFrequencies();
        }
        else if (choice == 3) {
            // Option 3: show histogram
            tracker.PrintHistogram('*');
        }
        else if (choice == 4) {
            // Option 4: exit program
            cout << "Goodbye." << endl;
            break;
        }
    }

    return 0;
}
