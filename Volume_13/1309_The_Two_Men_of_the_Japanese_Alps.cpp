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
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

typedef complex<double> Point;
const static double EPS = 1e-10;

double dot(const Point& p,const Point& q){
  return real(conj(p)*q);
}

double det(const Point& p,const Point& q){
  return imag(conj(p)*q);
}

bool on_seg(const Point& p1,const Point&p2,
	    const Point& q){
  return abs(det(p1-q,p2-q)) <= EPS && dot(p1-q,p2-q) < EPS;
}

Point compute_intersection(const Point& p1,const Point& p2,
			   const Point& q1,const Point& q2) {
  return p1 + (p2-p1) * det(q2-q1,q1-p1) / det(q2-q1,p2-p1);
}

int ccw(Point a,Point b,Point c) {
  b -= a; c -= a;
  if (det(b, c) > 0)   return +1;       // counter clockwise
  if (det(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

bool intersectSS(const Point& p1, const Point& p2,
		 const Point& q1, const Point& q2) {
  return (ccw(p1,p2,q1) *
	  ccw(p1,p2,q2) <= 0 &&
	  ccw(q1,q2,p1) *
	  ccw(q1,q2,p2) <= 0);
}

double compute_distance(const Point& p,const Point &q){
  return abs(q-p);
}

class State {
public:
  int lhs;
  int rhs;
};

int main(){
  int total_points;
  while(~scanf("%d",&total_points)){
    set<int> height;
    vector<Point> routes;
    for(int point_i = 0; point_i < total_points; point_i++){
      int x,y;
      scanf("%d %d",&x,&y);
      height.insert(y);
      routes.push_back(Point(x,y));
    }
    
    for(set<int>::iterator it = height.begin();
	it != height.end();
	it++){
      for(int route_i = 0; route_i+1 < routes.size(); route_i++){
	if(!intersectSS(routes[route_i],
			routes[route_i+1],
			Point(routes[route_i].real(),(double)*it),
			Point(routes[route_i+1].real(),(double)*it))){
	  continue;
	}

	Point p = compute_intersection(routes[route_i],
				       routes[route_i+1],
				       Point(routes[route_i].real(),(double)*it),
				       Point(routes[route_i+1].real(),(double)*it));

	if(p.real() - EPS <= routes[route_i].real() 
	   && routes[route_i].real() <= p.real() + EPS){
	  continue;
	}
	if(p.real() - EPS <= routes[route_i+1].real() 
	   && routes[route_i+1].real() <= p.real() + EPS){
	  continue;
	}
	cout << p.real() << " " << p.imag() << endl;
      }
    }
  }
}
