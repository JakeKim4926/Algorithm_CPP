#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <cmath>
#include <sstream>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N = 0, T = 0;
    int dp[11] = { 0, };
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i <= 10; i++)
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N;
        cout << dp[N] << "\n";
    }

    return 0;
}