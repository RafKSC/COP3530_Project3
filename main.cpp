#include <iostream>
#include <fstream>
#include <chrono> // used for time measurement
#include "RedBlackTreeNode.h"
#include "BTreeNode.h"

using namespace std;

vector<Vehicle> ReadAndStoreData(const string& filename) {
    vector<Vehicle> vehicles;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open vehicles.csv" << endl;
    }
    string line;
    // Skip header line
    getline(file, line);
    while (getline(file, line)) {
        if (line.empty())
            continue;
        Vehicle vehicle;
        if (vehicle.parseFromCsv(line))
            vehicles.push_back(vehicle);
        else
            cerr << "Error adding a row of data" << endl;
    }
    return vehicles;
}

int main()
{
    // Testing
    RBTree RBTree;
    BTree BTree;  // Add B-tree object

    // 0. Extract all data from .csv and store it in a vector.
    string filename = "../Electric_Vehicle_Population_Data.csv"; // CHANGE 2
    vector<Vehicle> vehicles = ReadAndStoreData(filename);

    cout << "Loading data into trees..." << endl;

    // 1. Insert all the data initially into both trees
    auto rbStart = chrono::high_resolution_clock::now();
    for (const auto& vehicle : vehicles) {
        RBTree.insert(vehicle);
    }
    auto rbEnd = chrono::high_resolution_clock::now();
    auto rbLoadTime = chrono::duration_cast<chrono::milliseconds>(rbEnd - rbStart);
    cout << "Red-Black Tree load time: " << rbLoadTime.count() << " milliseconds" << endl;

    // Load data into B-tree and measure time
    auto bStart = chrono::high_resolution_clock::now();

    for (const auto& vehicle : vehicles) {
        BTree.insert(vehicle);
    }

    auto bEnd = chrono::high_resolution_clock::now();
    auto bLoadTime = chrono::duration_cast<chrono::milliseconds>(bEnd - bStart);
    cout << "B-Tree load time: " << bLoadTime.count() << " milliseconds" << endl;

    bool end = false;
    while (!end)
    {
        cout << "\nMenu Options:" << endl;
        cout << "1. Find random data point in each data structure and compare" << endl;
        cout << "2. Search all trees for specific information and export" << endl;
        cout << "3. Delete random node and time operation" << endl;
        cout << "0. Exit program" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            // Generate random index
            srand(time(0));
            int index = rand() % vehicles.size();
            string randomVin = vehicles[index].getVin();

            cout << "\nRandom data point selected:" << endl;
            vehicles[index].printDetails();
            cout << endl;

            // Time RB-Tree search
            auto rbStart = chrono::high_resolution_clock::now();
            Vehicle* rbResult = RBTree.search(randomVin);
            auto rbEnd = chrono::high_resolution_clock::now();
            auto rbSearchTime = chrono::duration_cast<chrono::microseconds>(rbEnd - rbStart);

            // Time B-Tree search

            auto bStart = chrono::high_resolution_clock::now();
            Vehicle* bResult = BTree.search(randomVin);
            auto bEnd = chrono::high_resolution_clock::now();
            auto bSearchTime = chrono::duration_cast<chrono::microseconds>(bEnd - bStart);


            cout << "Search times:" << endl;
            cout << "Red-Black Tree: " << rbSearchTime.count() << " microseconds" << endl;
            cout << "B-Tree: " << bSearchTime.count() << " microseconds" << endl;
        }
        else if (choice == 2)
        {
            cout << "\nEnter search criteria:" << endl;
            cout << "1. Search by make" << endl;
            cout << "2. Search by model" << endl;
            cout << "3. Search by year" << endl;
            cout << "4. Search by type" << endl;

            int searchChoice;
            //string tempInput;

            //getline(cin, tempInput);
            // stringstream(tempInput) >> searchChoice;
            cin >> searchChoice;

            string attribute, value;
            switch (searchChoice) {
                case 1:
                    cout << "Enter make: ";
                    attribute = "make";
                    break;
                case 2:
                    cout << "Enter model: ";
                    attribute = "model";
                    break;
                case 3:
                    cout << "Enter year: ";
                    attribute = "year";
                    break;
                case 4:
                    cout << "Enter EV type: ";
                    attribute = "type";
                    break;
                default:
                    cout << "Invalid choice" << endl;
                    continue;
            }

            cin.ignore();
            getline(cin, value);

            //cin >> value;

            // Time RB-Tree search
            auto rbStart = chrono::high_resolution_clock::now();
            vector<Vehicle> rbResults = RBTree.searchByAttribute(attribute, value);
            auto rbEnd = chrono::high_resolution_clock::now();
            auto rbSearchTime = chrono::duration_cast<chrono::milliseconds>(rbEnd - rbStart);

            cout << "\nSearch results:" << endl;
            cout << "Red-Black Tree: Found " << rbResults.size() << " matches in "
                 << rbSearchTime.count() << " milliseconds" << endl;


            // Time B-Tree search

            auto bStart = chrono::high_resolution_clock::now();
            vector<Vehicle> bResults = BTree.searchByAttribute(attribute, value);
            auto bEnd = chrono::high_resolution_clock::now();
            auto bSearchTime = chrono::duration_cast<chrono::milliseconds>(bEnd - bStart);



            cout << "B-Tree: Found " << bResults.size() << " matches in "
                 << bSearchTime.count() << " milliseconds" << endl;


            string outputFile = value + "_" + attribute + "_results.csv";
            RBTree.exportToCSV(outputFile, rbResults);
            cout << "Results exported to " << outputFile << endl;
        }
        else if (choice == 3)
        {
            // Generate random index
            srand(time(0));
            int index = rand() % vehicles.size();
            string randomVin = vehicles[index].getVin();

            cout << "\nRandom vehicle selected for deletion:" << endl;
            vehicles[index].printDetails();
            cout << endl;

            // Time RB-Tree deletion
            auto rbStart = chrono::high_resolution_clock::now();
            RBTree.deleteNode(randomVin);
            auto rbEnd = chrono::high_resolution_clock::now();
            auto rbDeleteTime = chrono::duration_cast<chrono::microseconds>(rbEnd - rbStart);

            // Time B-Tree deletion

            auto bStart = chrono::high_resolution_clock::now();
            BTree.deleteKey(randomVin);
            auto bEnd = chrono::high_resolution_clock::now();
            auto bDeleteTime = chrono::duration_cast<chrono::microseconds>(bEnd - bStart);

            cout << "Deletion times:" << endl;
            cout << "Red-Black Tree: " << rbDeleteTime.count() << " microseconds" << endl;
            cout << "B-Tree: " << bDeleteTime.count() << " microseconds" << endl;



            // Remove from vector to keep it synchronized
            vehicles.erase(vehicles.begin() + index);
            cout << "Vehicle successfully deleted from trees and vector" << endl;
        }
        else if (choice == 0)
        {
            end = true;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}