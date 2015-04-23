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
#include <iterator>
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
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

Point crosspointLL(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
}

vector<Point> crosspointCL(const Circle &ci,const Line &l){
  //y = px + q
  // (x-a)^2 + (y-b)^2 = c^2
  double p = (imag(l[0]) - imag(l[1])) / (real(l[0]) - real(l[1]));
  double q = imag(l[1]) - p * real(l[1]);

  double a = ci.p.real();
  double b = ci.p.imag();
  double c = ci.r;

  double A = 1 + p * p;
  double B = (-2 * a - 2 * b * p + 2 * p * q);
  double C = a * a + b * b - 2 * q + q * q - c * c;
  vector<Point> res;
  if(B * B - 4 * A * C < -EPS) return res;
  if(-EPS <= B * B - 4 * A * C
     && B * B - 4 * A * C <= EPS) {
    double x = -B / (2 * A);
    double y = p * x + q;
    if(ccw(l[0],l[1],Point(x,y)) == 0){
      res.push_back(Point(x,y));
    }
    return res;
  }

  double x = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
  double y = p * x + q;
  if(ccw(l[0],l[1],Point(x,y)) == 0){
    res.push_back(Point(x,y));
  }
  
  x = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
  y = p * x + q;
  if(ccw(l[0],l[1],Point(x,y)) == 0){
    res.push_back(Point(x,y));
  }
  return res;
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
  int num_of_circumference_points;
  int num_of_polygon_vertices;
  while(~scanf("%d %d",
	       &num_of_circumference_points,
	       &num_of_polygon_vertices)){
    if(num_of_circumference_points == 0
       && num_of_polygon_vertices == 0) break;

    vector<double> points;
    for(int i = 0; i < num_of_circumference_points; i++){
      double p;
      cin >> p;
      points.push_back(p);
    }
  }
}
