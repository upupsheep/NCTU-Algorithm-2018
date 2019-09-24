#include "OJ.h"

#include <bits/stdc++.h>
using namespace std;

void swap(Point &a, Point &b) {
    Point tmp(a);
    a = b;
    b = tmp;
}

bool update(int n, vector<Point> &points) {
    // check whether current matching have intersection.
    // remove the intersection by swap two line and return 1
    // if no intersection return 0
    bool isIntersect = false;
    for (int i = 0; i < n; i++) {
        Line L1 = {points[i], points[n + i] - points[i]};
        for (int j = i + 1; j < n; j++) {
            Line L2 = {points[j], points[n + j] - points[j]};
            if (intersection(L1, L2)) {
                isIntersect = 1;
                swap(points[n + i], points[n + j]);
                Line L1 = {points[i], points[n + i] - points[i]};
                // break;
            }
        }
    }
    return isIntersect;
}

void partition(vector<Point> &points, vector<Point> &sub1,
               vector<Point> &sub2) {
    // find one straight line
    // points on one side store in vector sub1
    // points on the other side store in vector sub2
    // points on the straight line store in vector points
    //
    // Pi = points[0], Pj = points[n];
    // (Pi, Pk) cross (Pi, Pj)
    // d = a%b // a cross b
    // Point a = Pk - Pi, b = Pj - Pi;
    int n = points.size() / 2;
    for (int i = 0; i < n; i++) {
        for (int j = n; j < points.size(); j++) {
            Point b = points[j] - points[i];
            int l_rat = 0, l_hole = 0;
            for (int k = 0; k < n; k++) {
                Point a = points[k] - points[i],
                      a_hole = points[k + n] - points[i];

                if (a % b <= 0) {
                    l_rat++;
                }
                if (a_hole % b <= 0) {
                    l_hole++;
                }
            }
            if (l_rat == l_hole) {
                for (int k = 0; k < n; k++) {
                    Point a = points[k] - points[i],
                          a_hole = points[k + n] - points[i];
                    if (k == i) continue;
                    if (a % b < 0) {
                        sub1.push_back(points[k]);
                    } else {
                        sub2.push_back(points[k]);
                    }
                }
                for (int k = 0; k < n; k++) {
                    Point a = points[k] - points[i],
                          a_hole = points[k + n] - points[i];
                    if (n + k == j) continue;
                    if (a_hole % b < 0) {
                        sub1.push_back(points[n + k]);
                    } else {
                        sub2.push_back(points[n + k]);
                    }
                }
                vector<Point> tpoints;
                tpoints.push_back(points[i]);
                tpoints.push_back(points[j]);
                points.clear();
                points.assign(tpoints.begin(), tpoints.end());
                return;
            }
        }
    }
}

void naive(vector<Point> &points) {
    int n = (int)points.size() / 2;
    do {
        oj.set_match(points);
        display();
    } while (update(n, points));
}

void DC(vector<Point> &points) {
    // boundary case (naive) ...
    if (points.size() <= 4) {
        naive(points);
    } else {
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