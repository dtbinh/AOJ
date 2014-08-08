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

Point projection(const Line &l, const Point &p) {
  double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
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

vector<Point> compute_convex_hull(vector<Point>& ps){
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
  int x[4];
  int y[4];
  while(~scanf("%d %d",&x[0],&y[0])){
    if(x[0] == 0 && y[0] == 0) break;

    for(int i=1;i<4;i++){
      scanf("%d %d",&x[i],&y[i]);
    }
    int r;
    scanf("%d",&r);

    vector<Line> lines;
    vector<Point> points;

    for(int i=0;i<4;i++){
      points.push_back(Point(x[i],y[i]));
    }

    for(int i=0;i<3;i++){
      for(int j=i+1;j<3;j++){
	lines.push_back(Line(Point(x[i],y[i]),Point(x[j],y[j])));
      }
    }

    vector<Point> convex_hull = compute_convex_hull(points);

    if(convex_hull.size() == 3){
      double dist = numeric_limits<double>::max();
      for(int i=0;i<3;i++){
	dist = min(distanceLP(lines[i],Point(x[3],y[3])),dist);
      }

      if(r <= dist + EPS){
	//a
	printf("a\n");
      }
      else{
	dist = numeric_limits<double>::min();
	for(int i=0;i<3;i++){
	  dist = max(sqrt(dot(points[i]-points[3],points[i]-points[3])),dist);
	}
	if(r >= dist - EPS){
	  //b
	  printf("b\n");
	}
	else{
	  //c
	  printf("c\n");
	}

      }
    }

    else if(convex_hull.size() == 4){
      double dist = numeric_limits<double>::max();
      for(int i=0;i<3;i++){
	dist = min(distanceLP(lines[i],Point(x[3],y[3])),dist);
      }

      if(dist > r){
	//d
	printf("d\n");
      }
      else{
	dist = numeric_limits<double>::min();
	for(int i=0;i<3;i++){
	  dist = max(sqrt(dot(points[i]-points[3],points[i]-points[3])),dist);
	}
	
	if(r <= dist + EPS){
	  //b
	  printf("b\n");
	}
	else{
	  //c
	  printf("c\n");
	}
      }
    }

    else{
      assert(0);
    }
  }
}
