#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <cstdio>
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
#include <complex>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-12;

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

int main(){
  int n;
  while(~scanf("%d",&n)){
    if(n == 0) break;

    vector<Line> lines;
    lines.push_back(Line(Point(-100, 100),
			 Point(100, 100)));
    lines.push_back(Line(Point(100, 100),
			 Point(100, -100)));
    lines.push_back(Line(Point(100, -100),
			 Point(-100, -100)));
    lines.push_back(Line(Point(-100, -100),
			 Point(-100, 100)));
    int res = 1;
    for(int i = 0; i < n; i++){
      double x[2],y[2];
      scanf("%lf %lf %lf %lf",&x[0],&y[0],&x[1],&y[1]);
      lines.push_back(Line(Point(x[0],y[0]),Point(x[1],y[1])));

      vector<Point> points;
      for(int i = 0; i < lines.size() - 1; i++){
	if(intersectSS(lines[lines.size()-1],lines[i])){
	  Point candidate = crosspoint(lines[lines.size()-1],lines[i]);
	  if(abs(candidate.real()) > 100.0
	     || abs(candidate.imag()) > 100.0) continue;
	  for(int j = 0; j < points.size(); j++){
	    if(abs(candidate - points[j]) < EPS) goto next;
	  }
	  points.push_back(candidate);
	next:;
	}
      }
      
      res += points.size() - 1;
    }
    
    printf("%d\n",res);
  }
}
