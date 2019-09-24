#include <iostream>
#include <vector>
#include "lp_solver.h"
using namespace std;

/*
** optimize z = c^T y  (optimize: GLP_MIN or GLP_MAX)
** subject to Ay <= b
**
** return z
*/

// double lp_solver(int optimize, const vector<double>& c, const
// vector<vector<double> >& A, vector<double> &y, const vector<double> &b);

int main() {
    /*
     * The following code solves the linear program
     *
     * minimize    7 y1 + 11 y2 + 13 y3
     * subject to  y1 - y3 <= 1
     *             2 y1 + y2 + 3 y3 <= 2
     *
     *
     * i.e. return min{c^T y : Ay <= b}
     */
    int n, W, V;
    cin >> n >> W >> V;

    vector<vector<double> > A;
    A.resize(2 + 4 * n);
    for (int i = 0; i < (2 + 4 * n); ++i) {
        A[i].resize(n * 2);
    }
    for (int i = 0; i < 2 * n; i++)
        for (int j = 0; j < 2 * n; j++) A[i][j] = 0.0;

    // A[0][0] = 1, A[0][1] = 0, A[0][2] = -1;
    // A[1][0] = 2, A[1][1] = 1, A[1][2] = 3;
    for (int i = 0; i < n; i++) {
        double Wi;
        cin >> Wi;
        A[0][i * 2] = Wi;
        A[0][i * 2 + 1] = Wi;
    }
    for (int i = 0; i < n; i++) {
        double Vi;
        cin >> Vi;
        A[1][i * 2] = Vi;
        A[1][i * 2 + 1] = Vi;
    }
    for (int i = 0; i < 2 * n; i++) {
        A[i + 2][i] = 1;
        A[i + 2 + 2 * n][i] = -1;
    }

    vector<double> y;
    y.resize(n * 2);

    vector<double> b;
    b.resize(2 + 4 * n);
    b[0] = W, b[1] = V;
    for (int i = 0; i < 2 * n; i++) {
        b[i + 2] = 1;
        b[i + 2 + 2 * n] = 0;
    }

    vector<double> c;
    c.resize(n * 2);
    for (int i = 0; i < n; i++) {
        double Pi;
        cin >> Pi;
        c[i * 2] = Pi;
        c[i * 2 + 1] = Pi * 0.8;
    }

    double z = lp_solver(GLP_MAX, c, A, y, b);

    cout << z << endl;
    for (int i = 0; i < n; ++i) {
        cout << y[i * 2] + y[i * 2 + 1] << " ";
    }
    cout << endl;
    return 0;
}