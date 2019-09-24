#include "OJ.h"

#include <bits/stdc++.h>
using namespace std;

void swap(Point &a, Point &b)
{

    Point tmp(a);
    a = b;
    b = tmp;
}

bool update(int n, vector<Point> &points)
{
    // check whether current matching have intersection.
    // remove the intersection by swap two line and return 1
    // if no intersection return 0
    bool isIntersect = false;
    for (int i = 0; i < n; i++)
    {
        Line L1 = {points[i], points[n + i] - points[i]};
        for (int j = i + 1; j < n; j++)
        {
            Line L2 = {points[j], points[n + j] - points[j]};
            if (intersection(L1, L2))
            {
                isIntersect = 1;
                swap(points[n + i], points[n + j]);
                Line L1 = {points[i], points[n + i] - points[i]};
                //break;
            }
        }
    }
    return isIntersect;
}

void naive(vector<Point> &points)
{
    int n = (int)points.size() / 2;
    do
    {
        oj.set_match(points);
        display();
    } while (update(n, points));
}

void DC(vector<Point> &points)
{
    // boundary case (naive) ...
    if (points.size() <= 2048)
    {
        naive(points);
    }
    else
    {
        vector<Point> sub1, sub2;
        partition(points, sub1, sub2);
        // D&C ...
        DC(sub1);
        DC(sub2);
        DC(points);
        oj.set_match(sub1);
        oj.set_match(sub2);
        display();
    }
}