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

double compute_area(const Point &l,const Point &m){
  return abs(cross(l,m)) / 2.0;
}

bool is_equal(const Point &l,const Point &m){
  return ((abs(real(l) - real(m)) < EPS) && (abs(imag(l) - imag(m) < EPS)));
}

Point compute_circumcenter(const Point &l ,const Point & m,const Point &r){
  double angle_l = (atan2((m-l).imag(),(m-l).real()) - atan2((r-l).imag(),(r-l).real()));// * 180.0/M_PI;
  double angle_m = (atan2((l-m).imag(),(l-m).real()) - atan2((r-m).imag(),(r-m).real()));// * 180.0/M_PI;
  double angle_r = (atan2((l-r).imag(),(l-r).real()) - atan2((m-r).imag(),(m-r).real()));// * 180.0/M_PI;
  
  angle_l = (abs(angle_l) >= M_PI - EPS ? 2.0 * M_PI - abs(angle_l) : abs(angle_l));
  angle_m = (abs(angle_m) >= M_PI - EPS ? 2.0 * M_PI - abs(angle_m) : abs(angle_m));
  angle_r = (abs(angle_r) >= M_PI - EPS ? 2.0 * M_PI - abs(angle_r) : abs(angle_r));
  
  double length_m = dot(l - r,l - r);
  double length_l = dot(m - r,m - r);
  double length_r = dot(m - l,m - l);

  Point h = (l * tan(angle_l) + m * tan(angle_m) + r * tan(angle_r))/(tan(angle_l) + tan(angle_m) + tan(angle_r));
  return h;
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
    for(int i=0;i<3;i++){
      for(int j=i+1;j<3;j++){
	lines.push_back(Line(Point(x[i],y[i]),Point(x[j],y[j])));
      }
    }

    double dist = 1000000000.0;
    for(int i=0;i<3;i++){
      dist = min(distanceLP(lines[i],Point(x[3],y[3])),dist);
    }
    
    Point H = compute_circumcenter(Point(x[0],y[0]),Point(x[1],y[1]),Point(x[2],y[2]));
  }
}
