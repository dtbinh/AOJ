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
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

static const double EPS = 1e-10;

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

struct Circle {
  Point p; double r;
  Circle(const Point &p, double r) : p(p), r(r) { }
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

vector<Point> crosspointsCC(const Circle& s,const Circle& t){
  //ax + by + c = 0
  double a = real(t.p) - real(s.p); //x1-x2;
  double b = imag(t.p) - imag(s.p); //y1-y2;
  double d = sqrt(a * a + b * b);
  double theta = 0.0;

  if(d > 0) {
    theta = acos((d * d + s.r * s.r - t.r * t.r) / (2 * d * s.r));
  }

  double angle = atan2(b,a);
  
  vector<Point> res;
  if(d < s.r + t.r){
    res.push_back(Point(s.p.real() + s.r * cos(angle + theta), s.p.imag() + s.r * sin(angle + theta)));
    res.push_back(Point(s.p.real() + s.r * cos(angle - theta), s.p.imag() + s.r * sin(angle - theta)));
  }

  else if(s.r + t.r - EPS <= d && d <= s.r + t.r + EPS){
    res.push_back(Point(s.p.real() + s.r * cos(angle), s.p.imag() + s.r * sin(angle)));
  }
  
  return res;
}

Point crosspointLL(const Line &l, const Line &m) {
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

bool include(const Circle& s,Point t){
  t -= s.p;
  return dot(t,t) <= s.r * s.r + EPS;
}

int main(){
  int total_seals;
  while(~scanf("%d",&total_seals)){
    if(total_seals == 0) break;

    vector<Circle> circles;
    for(int i=0;i<total_seals;i++){
      double x,y;
      scanf("%lf,%lf",&x,&y);
      circles.push_back(Circle(Point(x,y),1.0));
    }

    vector<Point> points;
    for(int i=0;i<circles.size();i++){
      for(int j=i+1;j<circles.size();j++){
	
	vector<Point> cross_points;
	cross_points = crosspointsCC(circles[i],circles[j]);

	for(int k=0;k<cross_points.size();k++){
	  points.push_back(cross_points[k]);
	}
      }
    }
    
    int res = 1;

    for(int i=0;i<points.size();i++){
      int count = 0;
      for(int j=0;j<circles.size();j++){
	if(include(circles[j],points[i])){
	  count++;
	}
      }
      res = max(count,res);
    }
    printf("%d\n",res);
  }
}
