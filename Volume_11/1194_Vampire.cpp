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

bool intersectCS(const Circle& s,const Line& t){
  Point v = t[1] - t[0];
  Point c = s.p - t[0];
  Point b = s.p - t[1];
  if(dot(v,c) < 0){
    if(abs(c) < s.r) return true;
    return false;
  }
  else{
    if(dot(v,c) > dot(v,v)){
      if(dot(s.r,s.r) > dot(b,b)) return true;
      return false;
    }
    else{
      if(dot(c,c) - dot(v,c) * dot(v,c) / dot(v,v) < dot(s.r,s.r)) return true;
      if(abs(c) < s.r || abs(b) < s.r) return true;
      return false;
    }
  }
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
  int r,n;
  while(~scanf("%d %d",&r,&n)){
    if(r == 0 && n == 0) break;
    
    vector<Line> lines;
    double lhs = -(double)r;
    bool has_point[50][50] = {};
    int min_x = 100;
    int max_x = -100;
    double max_h = 0.0;
    for(int i = 0; i < n; i++){
      int lx,rx;
      int h;
      scanf("%d %d %d",&lx,&rx,&h);
      for(int x = lx; x < rx; x++){
	has_point[x + 20][h] = true;
      }
      min_x = min(lx,min_x);
      max_x = max(rx,max_x);
      max_h = max((double)h,max_h);
    }

    lines.push_back(Line(Point(-10000,0),Point(min_x,0)));
    lines.push_back(Line(Point(max_x,0),Point(10000,0)));

    for(int x = -20; x < 20; x++){
      bool isok = false;
      for(int y = 20; y >= 0; y--){
	if(has_point[x + 20][y]){
	  //horizontal
	  lines.push_back(Line(Point(x,y),Point(x+1,y)));

	  //vertical
	  lines.push_back(Line(Point(x,y),Point(x,100)));
	  lines.push_back(Line(Point(x+1,y),Point(x+1,100)));
	  isok = true;
	  break;
	}
      }
      if(!isok){
	  //horizontal
	lines.push_back(Line(Point(x,0),Point(x+1,0)));

	//vertical
	lines.push_back(Line(Point(x,0),Point(x,100)));
	lines.push_back(Line(Point(x+1,0),Point(x+1,100)));
      }
    }

    double rhs = max_h;
    for(int round = 0; round < 50; round++){
      double mid = lhs + (rhs - lhs) / 2.0;
      Circle c(Point(0,mid),r);
      
      bool has_crosspoint = false;
      for(int i = 0; i < lines.size(); i++){
	if(intersectCS(c,lines[i])){
	  has_crosspoint = true;
	  break;
	}
      }
      
      if(has_crosspoint){
	rhs = mid;
      }
      else{
	lhs = mid;
      }
    }
    printf("%.4lf\n",rhs + (double)r);
  }
}
