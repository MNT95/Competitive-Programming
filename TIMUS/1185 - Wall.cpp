#include <iostream>	
#include <time.h>
#include <vector>
#include <stdio.h>
#include <memory.h>
#include <string>
#include <map>
#include <algorithm>
#include <bitset>
#include <queue>
#include <set>
#include <time.h>
#include <assert.h>
#include <sstream>
//#include <unordered_map>
#include <bitset>
#include <utility>
#include <iomanip>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <math.h>
#include <cmath>
#include <complex>
#include <numeric>
#include <iomanip>
#if !ONLINE_JUDGE
#include "inc.h"
#endif
using namespace std;
typedef long long ll;


#define all(v)     ((v).begin()), ((v).end())
#define sz(v)      ((int)((v).size()))
#define clr(v, d)     memset(v, d, sizeof(v))
#define repa(v)   for(int i=0;i<(sz(v));++i) for(int j=0;j<(sz(v[i]));++j)
#define rep(i, v)      for(int i=0;i<(sz(v));++i)
#define lp(i, cnt)     for(int i=0;i<(cnt);++i)
#define lpi(i, s, cnt) for(int i=(s);i<(cnt);++i)
#define P(x)     cout<<#x<<" = { "<<x<<" }\n"
#define MP make_pair

typedef long long ll;
const int OO = (int)1e8;	// Note: Small->WRONG, Large->OVERFLOW

const double PI = acos(-1.0);

const double EPS = (1e-8);	// use lower carefully, e.g. for binary search

int dcmp(double a, double b) { return fabs(a - b) <= EPS ? 0 : a < b ? -1 : 1; }

typedef complex<double> point;
#define X real()
#define Y imag()
#define angle(a)                (atan2((a).imag(), (a).real()))
#define vec(a,b)                ((b)-(a))
#define same(p1,p2)             (dp(vec(p1,p2),vec(p1,p2)) < EPS)
#define dp(a,b)                 ( (conj(a)*(b)).real() )	// a*b cos(T), if zero -> prep
#define cp(a,b)                 ( (conj(a)*(b)).imag() )	// a*b sin(T), if zero -> parllel
#define length(a)               (hypot((a).imag(), (a).real()))
#define normalize(a)            (a)/length(a)
#define polar(r,ang)            ((r)*exp(point(0,ang))) 
#define rotateO(p,ang)          ((p)*exp(point(0,ang)))
#define rotateA(p,ang,about)  (rotateO(vec(about,p),ang)+about)

point reflect(point p, point p0, point p1) {
	point z = p - p0, w = p1 - p0;
	return conj(z / w)*w + p0; // Refelect point p1 around p0p1
}

struct angleCMP {
	point center;
	angleCMP(point c):center(c) { }
	bool operator()(const point &p0, const point p1)const {
		if(dcmp(cp(p0 - center, p1 - center), 0) == 0) {
			if(fabs(p0.Y - p1.Y)<EPS) {
				return p0.X<p1.X;
			}
			return p0.Y<p1.Y;
		}
		return cp(p0 - center, p1 - center)<0;
	}
};


vector<point> ConvexHull(vector<point> points) {
	if(sz(points) <= 1)	return points;

	rep(i, points) if(MP(points[i].Y, points[i].X) < MP(points[0].Y, points[0].X))
		swap(points[0], points[i]);

	sort(points.begin() + 1, points.end(), angleCMP(points[0]));

	vector<point> p, ch;

	
	//To remove co-linear points, un-comment this part
	rep(i, points) {
	if(sz(p) > 1 && !cp(p.back()-p[0], points[i]-p[0]) ) {
	if( length(points[0]-p.back()) < length(points[0]-points[i]) )
	p.back() = points[i];
	}
	else
	p.push_back( points[i] );
	}
	points = p;
	

	rep(i, points) {
		while(sz(ch) > 1 && cp(ch[sz(ch) - 2] - ch[sz(ch) - 1], points[i] - ch[sz(ch) - 1]) <= 0)
			ch.pop_back();	// ALSO Make it <= to remove co-linear points
		ch.push_back(points[i]);
	}
	return ch;
}

int n, l;


int main() {
#if !ONLINE_JUDGE
	freopen("a.txt", "r", stdin);
	//freopen("b.txt", "w", stdout);
	decTime;
#endif

	scanf("%d%d", &n, &l);
	vector<point>v;
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.push_back(point(x, y));
	}
	v = ConvexHull(v);
	int sz = v.size();
	v.push_back(v[0]);
	double ans = 0;
	for(int i = 0; i < sz; ++i) 
		ans += sqrt((v[i].X - v[i + 1].X)*(v[i].X - v[i + 1].X) + (v[i].Y - v[i + 1].Y)*(v[i].Y - v[i + 1].Y));
	ans += 2. * acos(-1)*l;
	printf("%.0lf\n", ans);



#if !ONLINE_JUDGE
	printTime;
#endif
	return 0;
}
