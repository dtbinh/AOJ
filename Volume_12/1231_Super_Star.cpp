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
  
static const double EPS = 1e-8;

class Point {
public:
  double _x;
  double _y;
  double _z;
  Point (double x,double y,double z) :
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
  void operator+=(const Point& p) const {
    _x + p._x;
    _y + p._y;
    _z + p._z;
  }
  Point operator*(const double t) const {
    return Point(_x * t,
		 _y * t,
		 _z * t);
  }
  Point operator*(const Point&p) const {
    return Point(_x * p._x,
		 _y * p._y,
		 _z * p._z);
  }
  Point operator/(const double t) const {
    return Point(_x / t,
		 _y / t,
		 _z / t);
  }
  void operator/=(const double t) {
    _x /= t;
    _y /= t;
    _z /= t;
  }
  void print_vec() const{
    printf("(%lf,%lf,%lf)\n",_x,_y,_z);
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

Point unit(const Point& p){
  return p/norm(p);
}

double dot(const Point& p1,const Point& p2){
  return p1._x * p2._x + p1._y * p2._y + p1._z * p2._z;
}

Point cross(const Point& p1,const Point& p2){
  return Point(p1._y * p2._z - p1._z * p2._y,
	       p1._z * p2._x - p1._x * p2._z,
	       p1._x * p2._y - p1._y * p2._x);
}

Point projection(const Line& l,const Point& p){
  double t = dot(p - l[0],l[0]-l[1]) / norm(l[0] - l[1]);
  return l[0] + unit(l[0] - l[1]) * t;
}

bool EQ(const Point& s,const Point& t) {
  if((t._x - EPS <= s._x && s._x <= t._x + EPS)
     && (t._y - EPS <= s._y && s._y <= t._y + EPS)
     && (t._z - EPS <= s._z && s._z <= t._z + EPS)) return true;
  return false;
}

bool parallelLL(const Line &l, const Line &m) {
  return EQ(cross(l[1]-l[0], m[1]-m[0]),Point(0,0,0));
}

bool intersectLP(const Line &l, const Point &p) {
  return (norm(cross(l[1]-p, l[0]-p)) < EPS);
}

double distanceLP(const Line& l,const Point& p){
  if(intersectLP(l,p)) return 0;
  return norm(p - projection(l,p));
}

double distanceLL(const Line& l,const Line& m){
  if(parallelLL(l,m)) return distanceLP(l,m[0]);

  const Point V1 = l[1] - l[0];
  const Point V2 = m[1] - m[0];
  const Point V3 = m[0] - l[0];
  return abs(dot(cross(V1,V2),V3)/norm(cross(V1,V2)));
}

double distancePP(const Point& s,const Point& t) {
  if(EQ(s,t)) return 0;
  return norm(Point(s._x - t._x,s._y - t._y,s._z - t._z));
}

const int sign[8][3] = {
  {+1,+1,+1},
  {+1,+1,-1},
  {+1,-1,+1},
  {+1,-1,-1},
  {-1,+1,+1},
  {-1,+1,-1},
  {-1,-1,+1},
  {-1,-1,-1}
};

class Cube {
public:
  Point _p;
  double _r;
  Cube(Point p,double r) : _p(p),_r(r) {}
  bool operator<(const Cube& c) const {
    return _r < c._r;
  }
  bool operator>(const Cube& c) const {
    return _r > c._r;
  }
};

int main(){
  int num_of_stars;
  while(~scanf("%d",&num_of_stars)){
    if(num_of_stars == 0) break;

    vector<Point> stars;
    Point center(0,0,0);
    for(int star_i = 0; star_i < num_of_stars; star_i++){
      double x,y,z;
      scanf("%lf %lf %lf",&x,&y,&z);
      stars.push_back(Point(x,y,z));
    }

    priority_queue<Cube,vector<Cube>,greater<Cube> > candidates;
    candidates.push(Cube(Point(50.0,50.0,50.0),1000.0));
    double min_radius = 1e15;

    double size = 100.0;

    while(size > 0.000002){
      size = size / 2.0;

      priority_queue<Cube,vector<Cube>,greater<Cube> > next;
      while(!candidates.empty()){
	for(int sign_i = 0; sign_i < 8; sign_i++){
	  Cube cube = candidates.top();
	  cube._p._x += sign[sign_i][0] * size / 2.0;
	  cube._p._y += sign[sign_i][1] * size / 2.0;
	  cube._p._z += sign[sign_i][2] * size / 2.0;

	  double r = 0.0;
	  for(int star_i = 0; star_i < stars.size(); star_i++){
	    r = max(r,distancePP(cube._p,stars[star_i]));
	  }

	  if(r < min_radius){
	    min_radius = r;
	  }
	  if(min_radius <= r - sqrt(3.0) * size / 2.0){
	    continue;
	  }
	  if(next.size() < 10000) next.push(Cube(cube._p,r));
	}
	candidates.pop();
      }
      candidates = next;
    }

    printf("%.5lf\n",min_radius);
  }
}
