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

double compute_area(const vector<Point>& polygon){
  double area = 0;
  for (int i = 0; i < polygon.size(); ++i) {
    area += cross(polygon[i], polygon[(i+1) % polygon.size()]);
  }
  return area;
}

int main(){
  int x1,y1,x2,y2;
  while(~scanf("%d %d %d %d",&x1,&y1,&x2,&y2)){
    if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) break;
    vector<Line> lines;
    lines.push_back(Line(Point(x1,y1),Point(x2,y2)));
    
    for(int i = 0; i < 2; i++){
      scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
      lines.push_back(Line(Point(x1,y1),Point(x2,y2)));
    }

    bool isok = true;
    
    vector<Point> polygon;
    for(int i=0;i<3;i++){
      for(int j=i+1;j<3;j++){
	if(intersectSS(lines[i],lines[j])){
	  Point p = crosspoint(lines[i],lines[j]);
	  polygon.push_back(p);
	}
	else{
	  isok = false;
	  goto ng;
	}
      }
    }
  ng:;

    double area = -1.0;
    if(isok){
      area = compute_area(polygon);
    }

    if(1900000.0 - EPS <= area){
      printf("%s\n","dai-kichi");
    }
    else if(1000000.0 - EPS <= area && area < 1900000.0){
      printf("%s\n","chu-kichi");
    }
    else if(100000.0 - EPS <= area && area < 1000000.0){
      printf("%s\n","kichi");
    }
    else if(0 - EPS <= area && area < 100000.0){
      printf("%s\n","syo-kichi");
    }
    else {
      printf("%s\n","kyo");
    }
  }
}
