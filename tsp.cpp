#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

const int INF = 1e9;

int tsp(int mask, int pos, vector<vector<int>>& dist, vector<vector<int>>& dp) {
    if (mask == (1 << dist.size()) - 1) {
        return dist[pos][0];
    }
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }
    
    int ans = INF;
    for (int city = 0; city < dist.size(); city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    auto start = chrono::high_resolution_clock::now();
    int result = tsp(1, 0, dist, dp);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Minimum cost: " << result << endl;
    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}

