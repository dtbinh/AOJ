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
#include <cctype>
#include <utility>
#include <complex>
#include <assert.h>

using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

typedef complex<double> Point;

namespace std {
  bool operator < (const Point& a, const Point& b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
  }
}

double compute_area(vector<Point>& points){
  double area = 0;
  for(int i = 0; i < points.size(); i++){
    area += (points[i].real() - points[(i + 1) % points.size()].real())
      * (points[i].imag() + points[(i + 1) % points.size()].imag());
  }
  return 1.0/2.0 * abs(area);
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

Point projection(const Line &l, const Point &p) {
  double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}
Point reflection(const Line &l, const Point &p) {
  return p + 2.0 * (projection(l, p) - p);
}

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

bool intersectLL(const Line &l, const Line &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
    abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}
bool intersectLS(const Line &l, const Line &s) {
  return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
    cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}
bool intersectLP(const Line &l, const Point &p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}
bool intersectSS(const Line &s, const Line &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
    ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP(const Line &s, const Point &p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

double distanceLP(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}
double distanceLS(const Line &l, const Line &s) {
  if (intersectLS(l, s)) return 0;
  return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const Line &s, const Point &p) {
  const Point r = projection(s, p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const Line &s, const Line &t) {
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
             min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}

double distanceLL(const Line &l, const Line &m) {
  return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}


Point crosspoint(const Line &l, const Line &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
  return m[0] + B / A * (m[1] - m[0]);
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

int main(){
  int N;
  while(~scanf("%d",&N)){
    vector<Point> points;
    double high,low,lhs,rhs;

    high = rhs = numeric_limits<double>::min();
    low = lhs = numeric_limits<double>::max();
    for(int pos_i = 0; pos_i < N; pos_i++){
      double x,y;
      scanf("%lf %lf",&x,&y);
      points.push_back(Point(x,y));
      low = min(low,y);
      high = max(high,y);

      lhs = min(lhs,x);
      rhs= max(rhs,x);
    }
    vector<Line> lines;
    for(int pos_i = 0; pos_i < N; pos_i++){
      lines.push_back(Line(points[pos_i],points[(pos_i+1) % N]));
    }

    double area_target;
    //horizontal line
    for(int round = 0; round < 50; round++){
      double mid = low + (high - low) / 2.0;
      Line horizontal_line(Point(-1000000.0,mid),Point(1000000.0,mid));

      vector<Point> div;
      for(int line_i = 0; line_i < lines.size(); line_i++){
	if(intersectLS(horizontal_line,lines[line_i])){
	  Point p = crosspoint(horizontal_line,lines[line_i]);
	  div.push_back(p);
	}
      }
      vector<Point> top,bottom;
      top.push_back(div[0]);
      top.push_back(div[1]);
      bottom.push_back(div[0]);
      bottom.push_back(div[1]);

      for(int pos_i = 0; pos_i < N; pos_i++){
	if(mid - EPS <= points[pos_i].imag()){
	  top.push_back(points[pos_i]);
	}
	if(mid + EPS >= points[pos_i].imag()){
	  bottom.push_back(points[pos_i]);
	}
      }
      top = compute_convex_hull(top);      
      bottom = compute_convex_hull(bottom);      
      double area_top = compute_area(top);
      double area_bottom = compute_area(bottom);
      double whole = area_top + area_bottom;

      if(area_top >= area_bottom){
	low = mid;
	area_target = area_top;
      }
      else{
	high = mid;
      }
    }

    //vertical line
    for(int round = 0; round < 50; round++){
      double mid = lhs + (rhs - lhs) / 2.0;
      Line vertical_line(Point(mid,-10000000.0),Point(mid,10000000.0));

      vector<Point> div;
      for(int line_i = 0; line_i < lines.size(); line_i++){
	if(intersectLS(vertical_line,lines[line_i])){
	  Point p = crosspoint(vertical_line,lines[line_i]);
	  div.push_back(p);
	}
      }

      vector<Point> left,right;
      left.push_back(div[0]);
      right.push_back(div[0]);
      left.push_back(div[1]);
      right.push_back(div[1]);

      for(int pos_i = 0; pos_i < N; pos_i++){
	if(mid - EPS >= points[pos_i].real()){
	  left.push_back(points[pos_i]);
	}
	if(mid + EPS <= points[pos_i].real()){
	  right.push_back(points[pos_i]);
	}
      }

      left = compute_convex_hull(left);
      right = compute_convex_hull(right);
      double area_left = compute_area(left);
      double area_right = compute_area(right);
      double whole = area_left + area_right;

      if(area_right >= area_left){
	lhs = mid;
      }
      else{
	rhs = mid;
      }
    }
    
    //check
    Line check_line(Point(lhs,low),Point(lhs + 1.0,low + 1.0));
    vector<Point> div;
    int first = -1;
    int last = -1;
    for(int line_i = 0; line_i < lines.size(); line_i++){
      if(intersectLS(check_line,lines[line_i])){
	Point p = crosspoint(check_line,lines[line_i]);
	div.push_back(p);
	if(first == -1) first = line_i;
	else if(last == -1) last = line_i;
      }
    }
    
    vector<Point> half;
    half.push_back(div[0]);

    for(int pos_i = 0; pos_i < N; pos_i++){
      if(first <= pos_i && pos_i <= last){
	half.push_back(points[pos_i]);
      }
    }
    half.push_back(div[1]);
    double area_half = compute_area(half);
    if(abs(area_half - area_target) > 0.01){
      cout << "NA" << endl;
    }
    else{
      printf("%.7lf %.7lf\n",lhs,low);
    }
  }
}
