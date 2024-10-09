#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Item {
    int value;
    int weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), compare);
    double totalValue = 0.0;

    for (auto& item : items) {
        if (capacity == 0) break;

        if (item.weight <= capacity) {
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            totalValue += item.value * ((double)capacity / item.weight);
            capacity = 0;
        }
    }
    return totalValue;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    int capacity = 50;
    vector<Item> items = { {60, 10, 6.0}, {100, 20, 5.0}, {120, 30, 4.0} };

    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }

    double maxValue = fractionalKnapsack(capacity, items);
    cout << "Maximum value in Knapsack = " << maxValue << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time taken: " << duration.count() << " seconds" << endl;

    return 0;
}

