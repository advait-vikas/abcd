#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

int matrixChainOrder(vector<int>& p, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][n - 1];
}

int main() {
    vector<int> p = {1, 2, 3, 4};
    int n = p.size();
    cout << "Minimum cost: " << matrixChainOrder(p, n) << endl;
    return 0;
}
