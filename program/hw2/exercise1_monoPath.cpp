#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int sol[1000][1000];
int M[1000][1000] = {0};

int Find(int x, int y) {
    if (sol[x][y] > -2) {
        return sol[x][y];
    }
    if (x == 0 && y == 0) {
        return sol[x][y] = 0;
    }
    if (x == 0) {
        if (sol[x][y - 1] > -1) {
            if (M[x][y - 1] == M[x][y - 1] + sol[x][y - 1] ||
                M[x][y] == M[x][y - 1] - sol[x][y - 1])
                return sol[x][y] = sol[x - 1][y];
            else
                return sol[x][y] = -1;
        }
    }
    if (y == 0) {
        if (sol[x - 1][y] > -1) {
            if (M[x][y] == M[x - 1][y] + sol[x - 1][y] ||
                M[x][y] == M[x - 1][y] - sol[x - 1][y])
                return sol[x][y] = sol[x - 1][y];
            else
                return sol[x][y] = -1;
        }
    }
    return sol[x][y] = min(max(abs(M[x][y] - M[x][y - 1]), Find(x, y - 1)),
                           max(abs(M[x][y] - M[x - 1][y]), Find(x - 1, y)));
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> M[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sol[i][j] = -2;  // -INF
        }
    }
    int result = Find(n - 1, n - 1);
    cout << result << endl;
    return 0;
}