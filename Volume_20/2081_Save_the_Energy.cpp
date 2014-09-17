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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class Point {
public:
  int _x;
  int _y;
  int _z;
  Point(int x,int y,int z) :
    _x(x), _y(y), _z(z) {}
  Point operator-(const Point& p) const {
    return Point(_x - p._x,
		 _y - p._y,
		 _z - p._z);
  }
  Point operator+(const Point& p) const {
    return Point(_x + p._x,
		 _y + p._y,
		 _z + p._z);
  }
  Point operator*(const double t) const {
    return Point(_x * t,
		 _y * t,
		 _z * t);
  }
};

class Line : public vector<Point> {
public:
  Line(const Point& p1,const Point& p2) {
    push_back(p1);
    push_back(p2);
  }
};


double norm(const Point& p){
  return sqrt(p._x * p._x + p._y * p._y + p._z * p._z);
}

double dot(const Point& p1,const Point& p2){
  return p1._x * p2._x + p1._y * p2._y + p1._z * p2._z;
}

double abs(const Point& p){
  return sqrt(dot(p,p));
}

Point cross(const Point& p1,const Point& p2){
  return Point(p1._y * p2._z - p1._z * p2._y,
	       p1._z * p2._x - p1._x * p2._z,
	       p1._x * p2._y - p1._y * p2._x);
}

Point projection(const Line& l,const Point& p){
  double t = dot(p - l[0],l[0]-l[1]) / norm(l[0] - l[1]);
  return l[0] + (l[0] - l[1]) * t;
}

Point reflection(const Line& l,const Point& p){
  return p + (projection(l,p) - p) * 2;
}

double distanceLP(const Line& l,const Point& p){
  return abs(p - projection(l,p));
}

bool intersectLL(const Line &l, const Line &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
    abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}

double distanceLL(const Line& l,const Line& m){
  return intersectLL(l,m) ? 0 : distanceLP(l,m[0]);
}

int main(){
  int num_of_straight_paths;
  while(~scanf("%d",&num_of_straight_paths)){
    int sx,sy,sz;
    int gx,gy,gz;
    scanf("%d %d %d",&sx,&sy,&sz);
    scanf("%d %d %d",&gx,&gy,&gz);
    
    vector<Line> lines;
    for(int path_i = 0; path_i < num_of_straight_paths; path_i++){
      int x[2],y[2],z[2];
      for(int i = 0; i < 2; i++){
	scanf("%d %d %d",&x[i],&y[i],&z[i]);
      }
      lines.push_back(Line(Point(x[0],y[0],z[0]),
			   Point(x[1],y[1],z[1])));
    }

    
  }
}
