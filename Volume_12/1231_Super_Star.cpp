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

int main(){
  int num_of_stars;
  while(~scanf("%d",&num_of_stars)){
    if(num_of_stars == 0) break;

    vector<Point> stars;
    for(int star_i = 0; star_i < num_of_stars; star_i++){
      double x,y,z;
      scanf("%lf %lf %lf",&x,&y,&z);
      stars.push_back(Point(x,y,z));
    }

    double max_radius = 0;
    for(int star_i = 0; star_i < num_of_stars; star_i++){
      for(int star_j = 0; star_j < num_of_stars; star_j++){
	if(star_i == star_j) continue;

	max_radius = max(max_radius,
			 distancePP(stars[star_i],stars[star_j])/2.0);
	
      }
    }

    printf("%.7lf\n",max_radius);
  }
}
