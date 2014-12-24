#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
 
static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};
 
static const double EPS = 1e-8;

typedef complex<double> Point;

namespace std {
  bool operator < (const Point& a, const Point& b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}

double cross(const Point& a, const Point& b) {
  return imag(conj(a)*b);
}
double dot(const Point& a, const Point& b) {
  return real(conj(a)*b);
}

struct Line : public vector<Point> {
  Line(const Point &a, const Point &b) {
    push_back(a); push_back(b);
  }
};

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

bool intersectSS(const Line &s, const Line &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
    ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}

Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}

double compute_area(const Point &l,const Point &m){
  return abs(cross(l,m)) / 2.0;
}

bool is_equal(const Point &l,const Point &m){
  return ((abs(real(l) - real(m)) < EPS) && (abs(imag(l) - imag(m) < EPS)));
}

double dp[1001];
bool tunnel[1001][1001];
bool is_top[1001];

int main(){
  int n;
  while(~scanf("%d",&n)){
    double vw,vc;    
    scanf("%lf %lf"&vw,&vc);
    vector<Point> points;
    for(int i = 0; i < n; i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      points.push_back(Point(x,y));
    }

    memset(is_top,false,sizeof(is_top));
    for(int i = 0; i < n; i++){
      if(i == 0){
	int next = i + 1;
	if(points[i].imag() > points[next].imag()){
	  is_top[i] = true;
	}
      }
      else if(i == n - 1){
	int prev = i - 1;
	if(points[prev].imag() < points[i].imag()){
	  is_top[i] = true;
	}
      }
      else{
	int prev = i - 1;
	int next = i + 1;
	if(points[prev].imag() < points[i].imag()
	   && points[i].imag() > points[next].imag()){
	  is_top[i] = true;
	}
      }
    }
    for(int i = 0; i < n; i++){
      int height = points[i].second;
      for(int j = i + 1; j < n; j++){
	if(height > points[i].second){
	  tunnel[i][j + 1] = true;
	}
      }
    }
  }
}
