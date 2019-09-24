#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int n;
void reset(vector<vector<bool>> &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            v[i][j] = 0;
        }
    }
    for (int i = 0; i <= n; i++) {
        v[i][0] = 0;
        v[0][i] = 0;
    }
    v[1][1] = 1;
}
void show(vector<vector<bool>> &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j];
        }
        cout << '\n';
    }
}

int main() {

    cin >> n;
    vector<vector<char>> grid;
    vector<vector<bool>> canget;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid.push_back(vector<char>(n, ' '));
            canget.push_back(vector<bool>(n, 0));
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i <= n; i++) {
        canget[i][0] = 1;
        canget[0][i] = 1;
    }
    canget[1][1] = 1;

    // 免費雙色
    if (grid[1][1] != grid[n][n]) {
        char a = grid[1][1];
        char b = grid[n][n];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (canget[i - 1][j] || canget[i][j - 1]) {
                    if (grid[i][j] == a || grid[i][j] == b) {
                        canget[i][j] = 1;
                    }
                }
            }
        }

        if (canget[n][n] == 1) {
            cout << "Yes" << '\n';
            return 0;
        }
    } else {
        char a = grid[1][1];
        for (int c = 0; c < 26; c++) {
            char b = (char)('a' + c);
            if (a == b)
                continue;
            reset(canget);
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (canget[i - 1][j] || canget[i][j - 1]) {
                        if (grid[i][j] == a || grid[i][j] == b) {
                            canget[i][j] = 1;
                        }
                    }
                }
            }

            if (canget[n][n] == 1) {
                cout << "Yes" << '\n';
                return 0;
            }
        }
    }

    cout << "No" << '\n';
    return 0;
}