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

bool intersectCC(const Circle &s, const Circle &t) {
  double abs_distance
    = (imag(s.p) - imag(t.p)) * (imag(s.p) - imag(t.p))
    + (real(s.p) - real(t.p)) * (real(s.p) - real(t.p));
  // cout << "abs " << abs_distance << ":" << (s.r + t.r) * (s.r + t.r) <<endl;

  return (abs_distance <= (s.r + t.r) * (s.r + t.r));
}

vector<Point> cli(double a,double b,double c,
	     const Circle & s){
  //ax + by + c = 0
  double l = a * a + b * b;
  double k = a * real(s.p) + b * imag(s.p) + c;
  double d = l * s.r * s.r - k * k;

  vector<Point> res;
  if(d > 0){
    double ds = sqrt(d);
    double apl = a/l;
    double bpl = b/l;
    double xc = real(s.p) - apl * k;
    double yc = imag(s.p) - bpl * k;
    double xd = bpl * ds;
    double yd = apl * ds;

    res.push_back(Point(xc - xd,yc + yd));
    res.push_back(Point(xc + xd,yc - yd));
  }else if(d==0){
    res.push_back(Point(real(s.p) - a * k/l,imag(s.p) - b * k/l));
  }else{
    //nothing to do
  }

  return res;
}

vector<Point> crosspointsCC(const Circle& s,const Circle& t){
  //ax + by + c = 0
  double a = real(s.p) - real(t.p); //x1-x2;
  double b = imag(s.p) - imag(t.p); //y1-y2;
  double c = 0.5 * ((s.r - t.r)*(s.r + t.r)
		    - a * (real(s.p)+real(t.p))
		    - b * (imag(s.p)+imag(t.p)));

  return cli(a,b,c,s);
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

    vector<Line> lines;
    vector<Point> points;
    for(int i=0;i<circles.size();i++){
      for(int j=i+1;j<circles.size();j++){
	
	vector<Point> cross_points;
	if(intersectCC(circles[i],circles[j])){
	  cross_points = crosspointsCC(circles[i],circles[j]);
	}

	if(cross_points.size() == 1){
	  points.push_back(cross_points[0]);

	}
	else if(cross_points.size() == 2){
	  lines.push_back(Line(cross_points[0],cross_points[1]));
	  printf("(%lf,%lf)",real(cross_points[0]),imag(cross_points[0]));
	  printf(" -> (%lf,%lf)\n",real(cross_points[1]),imag(cross_points[1]));
	}
      }
    }
    
    int res = 0;
    
    //for point
    for(int i=0;i<points.size();i++){
      int tmp_max = 1;
      for(int j=0;j<points.size();j++){
	if(i == j) continue;
	if(is_equal(points[i],points[j])){
	  tmp_max++;
	}
      }
      for(int j=0;j<lines.size();j++){
	if(ccw(lines[j][0],points[i],lines[j][1]) == -2){
	  tmp_max++;
	}
      }

      res = max(tmp_max,res);
    }

    
    //for line
    for(int i=0;i<lines.size();i++){
      int tmp_max = 1;
      for(int j=0;j<points.size();j++){
	if(ccw(lines[i][0],points[j],lines[i][1]) == -2){
	  tmp_max++;
	}
      }
      for(int j=0;j<lines.size();j++){
	if(i == j) continue;
	if(intersectSS(lines[i],lines[j])){
	  tmp_max++;
	}
      }

      res = max(tmp_max,res);
    }

    printf("%d\n",res);
  }
}
