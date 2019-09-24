#ifndef __POINT__
#define __POINT__

#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct Point
{
    long long x, y;
    int id, color;

    Point operator+(const Point &b) const
    {
        return {x + b.x, y + b.y, -1, -1};
    }
    Point operator-(const Point &b) const
    {
        return {x - b.x, y - b.y, id, color};
    }
    long long operator%(const Point &b) const
    {
        return x * b.y - y * b.x;
    }
    long long operator*(const Point &b) const
    {
        return x * b.x + y * b.y;
    }
};

struct Line
{
    Point p, v;
};

int sgn(long long x)
{
    if (x < 0)
        return -1;
    if (x > 0)
        return 1;
    return 0;
}

bool intersection(const Line &a, const Line &b)
{
    if (sgn((b.p - a.p) % a.v) * sgn(a.v % (b.p + b.v - a.p)) < 0)
        return 0;
    if (sgn((a.p - b.p) % b.v) * sgn(b.v % (a.p + a.v - b.p)) < 0)
        return 0;
    return 1;
}

void ConvexHull(vector<Point> &P, vector<Point> &H)
{
    int n = P.size(), m = 0;
    sort(P.begin(), P.end(), [](const Point &a, const Point &b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    });
    H.clear();

    for (int i = 0; i < n; i++)
    {
        while (m >= 2 && (P[i] - H[m - 2]) % (H[m - 1] - H[m - 2]) < 0)
            H.pop_back(), m--;
        H.push_back(P[i]), m++;
    }

    for (int i = n - 2; i >= 0; i--)
    {
        while (m >= 2 && (P[i] - H[m - 2]) % (H[m - 1] - H[m - 2]) < 0)
            H.pop_back(), m--;
        H.push_back(P[i]), m++;
    }
}

#endif