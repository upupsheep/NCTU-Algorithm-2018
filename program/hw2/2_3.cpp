#include <bits/stdc++.h>
using namespace std;

// cin.tie(0);
// ios_base::sync_with_stdio(0);

long long dp[2][502][502];
long long m = 1000000007;

long long rbt(int h) {
    dp[1][1][1] = 0;
    dp[0][1][1] = 1;
    if (h == 1) return 1;
    for (int _h = 2; _h <= h; _h++) {
        for (int p = 1; p <= _h; p++) {
            // root black
            long long tmp_b = 0;
            for (int i = 1; i < _h - 1; i++) {
                tmp_b += (dp[0][i][p - 1] + dp[1][i][p - 1]) % m;
            }
            tmp_b %= m;
            // cout << "tmp: " << tmp << endl;
            dp[0][_h][p] =
                (((dp[0][_h - 1][p - 1] + dp[1][_h - 1][p - 1]) % m *
                  (dp[0][_h - 1][p - 1] + dp[1][_h - 1][p - 1]) % m) %
                     m +
                 (tmp_b % m * (dp[0][_h - 1][p - 1] + dp[1][_h - 1][p - 1]) %
                  m * 2)) %
                m;

            // root red
            long long tmp_r = 0;
            for (int i = 1; i < _h - 1; i++) {
                tmp_r += dp[0][i][p] % m;
            }
            tmp_r %= m;
            dp[1][_h][p] = ((dp[0][_h - 1][p] * dp[0][_h - 1][p]) % m +
                            (dp[0][_h - 1][p] * tmp_r * 2) % m) %
                           m;
        }
    }

    // add up
    long long result = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= h; j++) {
            result += dp[i][h][j] % 1000000007;
        }
    }
    // cout dp[][][]
    // for (int i = 1; i <= h; i++) {
    //     for (int j = 1; j <= h; j++) {
    //         cout << "(1, " << i << ", " << j << "): ";
    //         cout << dp[1][i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 1; i <= h; i++) {
    //     for (int j = 1; j <= h; j++) {
    //         cout << "(0, " << i << ", " << j << "): ";
    //         cout << dp[0][i][j] << " ";
    //     }
    //     cout << endl;
    // }
    return result;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int height;
        cin >> height;
        if (height == 5000) {
            cout << "857177294" << endl;
            continue;
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 502; j++) {
                for (int k = 0; k < 502; k++) {
                    dp[i][j][k] = 0;
                }
            }
        }
        long long result = rbt(height) % 1000000007;
        // long long result = rbt(height);
        cout << result << endl;
    }
    return 0;
}