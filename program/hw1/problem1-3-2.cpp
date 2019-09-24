#include "OJ.h"
#include <bits/stdc++.h>
using namespace std;
bool update(int n, vector<Point> &points){
	vector<Line> L(n);
	for(int i = 0 ; i < n ; i++)
		L[i] = {points[i],points[i+n]-points[i]};
	int nope = 0;
	for(int a = 0 ; a < n ; a++){
		for(int b = a+1 ; b < n ; b++){
			if(intersection(L[a],L[b])){
				swap(points[a+n],points[b+n]);
				L[a] = {points[a],points[a+n]-points[a]};
				L[b] = {points[b],points[b+n]-points[b]};
				nope = 1;
			}
		}
	}
	return nope;
}
void ppartition(vector<Point> &points, vector<Point> &sub1, vector<Point> &sub2){
	int n = points.size()/2;
	vector<Line> line(n);
	for(int i = 0 ; i < n ; i++){
		for(int j = n ; j < n*2 ; j++){
			line[i] = {points[i],points[j]-points[i]};
		}
	}
	for(int i = 0 ; i < n ; i++){
		for(int j = 0 ; j < 2*n ; j++){
			int count_blue = 0, count_red = 0;
			sub1.clear();
			sub2.clear();
			Point p_test = points[j]-points[i];
			if(p_test%line[i].v > 0){
				sub1.push_back(points[j]);
				switch(points[j].color){
					case 0:
						count_red++;
						break;
					case 1:
						count_blue++;
						break;
				}
			}
			else sub2.push_back(points[j]);
			
			if(count_blue == count_red && count_blue != 0){
				points.clear();
				points.push_back(points[i]);
				points.push_back(line[i].v + points[i]);
				return;
			}
		}
	}
}
void naive(vector<Point> &points){
    int n = (int) points.size()/2;
    while ( update(n,points) );
    oj.set_match(points);
    display();
}
void DC(vector<Point> &points){
    if(points.size() <= 20000){
    	naive(points);
    	display();
    	return;
	}
    vector<Point> sub1, sub2;
    ppartition(points,sub1,sub2);
    naive(points);
    oj.set_match(sub1);
    DC(sub1);
    oj.set_match(sub2);
	DC(sub2);
	display();
}
