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
#include <assert.h>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <double,P> PP;
  
static const double EPS = 1e-8;

class Point {
public:
  double x;
  double y;
  double z;
  Point (double x,double y,double z) :
    x(x), y(y), z(z) {}
  Point () : x(0), y(0), z(0) {}
  Point operator-(const Point& p) const {
    return Point(this->x - p.x,
		 this->y - p.y,
		 this->z - p.z);
  }
  Point operator+(const Point& p) const {
    return Point(this->x + p.x,
		 this->y + p.y,
		 this->z + p.z);
  }
  void operator+=(const Point& p) const {
    this->x + p.x;
    this->y + p.y;
    this->z + p.z;
  }
  Point operator*(const double t) const {
    return Point(this->x * t,
		 this->y * t,
		 this->z * t);
  }
  Point operator*(const Point&p) const {
    return Point(this->x * p.x,
		 this->y * p.y,
		 this->z * p.z);
  }
  void operator*=(const double t) const {
    this->x * t;
    this->y * t;
    this->z * t;
  }
  void operator*=(const Point&p) const {
    this->x * p.x;
    this->y * p.y;
    this->z * p.z;
  }

  Point operator/(const double t) const {
    return Point(this->x / t,
		 this->y / t,
		 this->z / t);
  }
  void operator/=(const double t) {
    this->x /= t;
    this->y /= t;
    this->z /= t;
  }
  void print_vec() const{
    printf("(%lf,%lf,%lf)\n",this->x,this->y,this->z);
  }
};

class Line : public vector<Point> {
public:
  Line(const Point& p1,const Point& p2) {
    push_back(p1);
    push_back(p2);
  }
};

class Circle {
public:
  Point p;
  double r;
  Circle(const Point& p,double r) : p(p),r(r) {}
};

double norm(const Point& p){
  return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

Point unit(const Point& p){
  return p/norm(p);
}

double dot(const Point& p1,const Point& p2){
  return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

Point cross(const Point& p1,const Point& p2){
  return Point(p1.y * p2.z - p1.z * p2.y,
	       p1.z * p2.x - p1.x * p2.z,
	       p1.x * p2.y - p1.y * p2.x);
}

Point projection(const Line& l,const Point& p){
  double t = dot(p - l[0],l[0]-l[1]) / norm(l[0] - l[1]);
  return l[0] + unit(l[0] - l[1]) * t;
}

bool EQ(const Point& s,const Point& t) {
  if((t.x - EPS <= s.x && s.x <= t.x + EPS)
     && (t.y - EPS <= s.y && s.y <= t.y + EPS)
     && (t.z - EPS <= s.z && s.z <= t.z + EPS)) return true;
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
  return norm(Point(s.x - t.x,s.y - t.y,s.z - t.z));
}

vector<Point> crosspointLC(const Line& l,const Circle& ci){
  Point dv = unit(l[1] - l[0]);
  // a * t^2 + b * t + c = 0
  double a = dv.x * dv.x + dv.y * dv.y + dv.z * dv.z;
  double b = 2.0 * ((l[0].x * dv.x - dv.x * ci.p.x)
		    + (l[0].y * dv.y - dv.y * ci.p.y)
		    + (l[0].z * dv.z - dv.z * ci.p.z));
  double c = (l[0].x * l[0].x + l[0].y * l[0].y + l[0].z * l[0].z)
    + (ci.p.x * ci.p.x + ci.p.y * ci.p.y + ci.p.z * ci.p.z)
    - 2.0 * ((l[0].x * ci.p.x) + (l[0].y * ci.p.y) + (l[0].z * ci.p.z))
    - (ci.r * ci.r);
  double D = b * b - 4.0 * a * c;

  vector<Point> res;
  if(D < 0) return res;
  
  double t1 = (-b - sqrt(D))/(2.0 * a);
  double t2 = (-b + sqrt(D))/(2.0 * a);
  res.push_back(l[0] + dv * t1);
  res.push_back(l[0] + dv * t2);
  return res;
}

Point reflection(const Line& l,const Point& p){
  return p + (projection(l,p) - p) * 2.0;
}

int main(){
  int num_of_spheres;
  while(~scanf("%d",&num_of_spheres)){
    if(num_of_spheres == 0) break;

    int u,v,w;
    scanf("%d %d %d",&u,&v,&w);

    vector<Circle> spheres;
    for(int sphere_i = 0; sphere_i < num_of_spheres; sphere_i++){
      int x,y,z,r;
      scanf("%d %d %d %d",&x,&y,&z,&r);
      spheres.push_back(Circle(Point(x,y,z),r));
    }

    Point reflection_point;
    Line laser(Point(0,0,0),Point(u,v,w));

    int prev_sphere = -1;
    for(int round = 0; round < 100; round++){
      double min_norm = numeric_limits<double>::max();
      int current_sphere = -1;
      for(int sphere_i = 0; sphere_i < num_of_spheres; sphere_i++){
	if(prev_sphere == sphere_i) continue;
	vector<Point> p = crosspointLC(laser,spheres[sphere_i]);
	for(int i = 0; i < p.size(); i++){
	  if(norm(p[i] - laser[0]) < min_norm){
	    reflection_point = p[i];
	    current_sphere = sphere_i;
	    min_norm = norm(p[i] - laser[0]);
	  }
	}
      }
      if(current_sphere == -1) break;

      Line nv(spheres[current_sphere].p,reflection_point);
      laser = Line(reflection_point,
		   reflection(nv,laser[0]));

      prev_sphere = current_sphere;
    }

    printf("%.4lf %.4lf %.4lf\n",
	   reflection_point.x,
	   reflection_point.y,
	   reflection_point.z);

  }
}
