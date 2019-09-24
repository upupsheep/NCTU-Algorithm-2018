#include <bits/stdc++.h>
using namespace std;

// Returns length of LCS
// for X[0..m-1], Y[0..n-1]
int LCS(string &X, string &Y) {
    // Find lengths of two strings
    int m = X.length(), n = Y.length();

    int L[2][n + 1];

    // Binary index, used to
    // index current row and
    // previous row.
    bool bi;
    int cnt = m + 1;
    for (int i = 0; i <= m; i++) {
        // Compute current
        // binary index
        bi = i & 1;

        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[bi][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                L[bi][j] = L[1 - bi][j - 1] + 1;

            else
                L[bi][j] = max(L[1 - bi][j], L[bi][j - 1]);

            // cout << L[bi][j] << " ";
        }
        // cout << endl;
        if (cnt <= m && cnt >= 1) cout << 2 * L[bi][cnt] - 1 << " ";
        cnt -= 1;
    }

    // Last filled entry contains
    // length of LCS
    // for X[0..n-1] and Y[0..m-1]
    return L[bi][n];
}

int main() {
    string str;
    cin >> str;
    // vector<int> f;
    string r_str = str;
    reverse(r_str.begin(), r_str.end());
    int result = LCS(str, r_str);
    cout << endl;
    // long long test = 857177294;
    // cout << test << endl;
    return 0;
}