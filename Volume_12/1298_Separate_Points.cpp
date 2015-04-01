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

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

bool is_inner(Point a, Point b, Point c) {
  b -= a; c -= a;
  return (dot(b,c) <= 0);
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

Point projection(const Line &l, const Point &p) {
  double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}

bool is_projection_on_line(const Line &l, const Point &p) {
  Point pj = projection(l,p);
  return is_inner(pj,l[0],l[1]);
}

double distanceLP(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}

bool is_equal(const Point &l,const Point &m){
  return ((abs(real(l) - real(m)) < EPS) && (abs(imag(l) - imag(m) < EPS)));
}

bool cmp_x(const Point& p, const Point& q){
  if(p.real() != q.real()) return p.real() < q.real();
  return p.imag() < q.imag();
}

vector<Point> compute_convex_hull(vector<Point> ps){
  sort(ps.begin(), ps.end(), cmp_x);
  int k = 0;
  vector<Point> qs(ps.size() * 2);
  for(int i=0; i < ps.size(); i++){
    while(k > 1 && cross(qs[k - 1] - qs[k - 2],ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  for(int i = ps.size() - 2,t = k; i >= 0; i--){
    while(k > t && cross(qs[k - 1] - qs[k - 2],ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k-1);
  return qs;
}

bool is_convex_hull(vector<Point>& ps,const Point& c){
  for(int i=0;i<ps.size();i++){
    if(is_equal(ps[i],c)) return true;
  }
  return false;
}

bool is_inner_polygon(const vector<Point>& outer,const vector<Point>& inner){

  Point center;
  for(int i = 0; i < outer.size(); i++){
    center += outer[i];
    for(int j = 0; j < inner.size(); j++){
      if(ccw(outer[i],outer[(i+1) % outer.size()],inner[j]) == 0){
	return true;
      }
    }
  }
  center /= outer.size();
  for(int i = 0; i < inner.size(); i++){
    for(int j = 0; j < outer.size(); j++){
      double a = cross(center - outer[j],inner[i] - center);
      double b = cross(outer[j] - outer[(j+1) % outer.size()],inner[i] - outer[j]);
      double c = cross(outer[(j+1) % outer.size()] - center,inner[i] - outer[(j+1) % outer.size()]);

      if((a > 0 && b > 0 && c > 0)
	 || (a < 0 && b < 0 && c < 0)){
	return true;
      }
    }
  }

  return false;
}

int main(){
  int n,m;
  while(~scanf("%d %d",&n,&m)){
    if(n == 0 && m == 0) break;

    vector<Point> white;
    for(int i = 0; i < n; i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      white.push_back(Point(x,y));
    }
    vector<Point> white_convex_hull = compute_convex_hull(white);

    vector<Point> black;
    for(int i = 0; i < m; i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      black.push_back(Point(x,y));
    }
    vector<Point> black_convex_hull = compute_convex_hull(black);

    bool dividable = true;

    if(black_convex_hull.size() == 1 && white_convex_hull.size() == 2){
      if(ccw(white_convex_hull[0],white_convex_hull[1],black_convex_hull[0]) == 0){
	dividable = false;
      }
    }
    else if(black_convex_hull.size() == 2 && white_convex_hull.size() == 1){
      if(ccw(black_convex_hull[0],black_convex_hull[1],white_convex_hull[0]) == 0){
	dividable = false;
      }
    }
    else if(black_convex_hull.size() == 2 && white_convex_hull.size() == 2){
      if(intersectSS(Line(black_convex_hull[0],black_convex_hull[1]),
		     Line(white_convex_hull[0],white_convex_hull[1]))){
	dividable = false;
      }
    }
    else {
      if(black_convex_hull.size() >= 3 && is_inner_polygon(black_convex_hull,white_convex_hull)
	 || white_convex_hull.size() >= 3 && is_inner_polygon(white_convex_hull,black_convex_hull)){
	dividable = false;
      }
    }
    printf("%s\n", dividable ? "YES" : "NO");
  }
}
