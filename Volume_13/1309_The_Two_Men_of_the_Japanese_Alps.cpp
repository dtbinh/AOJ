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
const static double EPS = 1e-8;

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

struct State {
  int lhs;
  int rhs;
  double cost;
  State(int l,int r,int c) : lhs(l),rhs(r),cost(c) {}
  bool operator<(const State& s) const {
    return cost < s.cost;
  }
  bool operator>(const State& s) const {
    return cost > s.cost;
  }
};

struct Node {
  Point point;
  bool is_origin;
  Node(Point p, bool o) : point(p), is_origin(o) {}
  bool operator<(const Node& n) const{
    return point.real() < n.point.real();
  }
  bool operator>(const Node& n) const{
    return point.real() > n.point.real();
  }
};

double dp[1001][1001];

void disp(int next_cost,int lhs_i,int rhs_i){
  cout << next_cost << endl;
  cout << dp[lhs_i][rhs_i] << endl;
  cout << lhs_i << " " << rhs_i << endl;

}
int main(){
  int total_points;
  while(~scanf("%d",&total_points)){
    set<int> height;
    vector<Node> routes;
    for(int point_i = 0; point_i < total_points; point_i++){
      int x,y;
      scanf("%d %d",&x,&y);
      height.insert(y);
      routes.push_back(Node(Point(x,y),true));
    }
    
    vector<Node> external;
    for(set<int>::iterator it = height.begin();
	it != height.end();
	it++){
      for(int route_i = 0; route_i+1 < routes.size(); route_i++){
	if(!intersectSS(routes[route_i].point,
			routes[route_i+1].point,
			Point(routes[route_i].point.real(),(double)*it),
			Point(routes[route_i+1].point.real(),(double)*it))){
	  continue;
	}

	Point p = compute_intersection(routes[route_i].point,
				       routes[route_i+1].point,
				       Point(routes[route_i].point.real(),(double)*it),
				       Point(routes[route_i+1].point.real(),(double)*it));

	if(p.real() - EPS <= routes[route_i].point.real() 
	   && routes[route_i].point.real() <= p.real() + EPS){
	  continue;
	}
	if(p.real() - EPS <= routes[route_i+1].point.real() 
	   && routes[route_i+1].point.real() <= p.real() + EPS){
	  continue;
	}
	external.push_back(Node(p,false));
      }
    }

    for(int ext_i = 0; ext_i < external.size(); ext_i++){
      routes.push_back(external[ext_i]);
    }

    sort(routes.begin(),routes.end());
    fill((double*)dp,(double*)dp+1001*1001,10000000000000.0);

    priority_queue<State,vector<State>,greater<State> > que;
    que.push(State(0,routes.size() - 1,0.0));
    dp[0][routes.size()-1] = 0.0;

    while(!que.empty()){
      State s = que.top();
      que.pop();

      for(int lhs_i = s.lhs + 1; lhs_i < routes.size(); lhs_i++){
	if(routes[lhs_i].is_origin){
	  // to right

	  for(int rhs_i = s.rhs + 1; rhs_i < routes.size(); rhs_i++){
	    if(abs(routes[rhs_i].point.imag() - routes[lhs_i].point.imag()) < EPS){
	      double next_cost = s.cost 
		+ compute_distance(routes[s.lhs].point,routes[lhs_i].point)
		+ compute_distance(routes[s.rhs].point,routes[rhs_i].point);
	      if(next_cost < dp[lhs_i][rhs_i]){
		disp(next_cost,lhs_i,rhs_i);
		dp[lhs_i][rhs_i] = next_cost;
		que.push(State(lhs_i,rhs_i,next_cost));
	      }
	      break;
	    }
	    if(routes[rhs_i].is_origin) break;
	  }
	  
	  // to left
	  for(int rhs_i = s.rhs - 1; rhs_i >= 0; rhs_i--){
	    if(abs(routes[rhs_i].point.imag() - routes[lhs_i].point.imag()) < EPS){
	      double next_cost = s.cost 
		+ compute_distance(routes[s.lhs].point,routes[lhs_i].point)
		+ compute_distance(routes[s.rhs].point,routes[rhs_i].point);
	      if(next_cost < dp[lhs_i][rhs_i]){
		disp(next_cost,lhs_i,rhs_i);
		dp[lhs_i][rhs_i] = next_cost;
		que.push(State(lhs_i,rhs_i,next_cost));
	      }
	      break;
	    }
	    if(routes[rhs_i].is_origin) break;
	  }
	  break;
	}
      }

      for(int lhs_i = s.lhs - 1; lhs_i >= 0; lhs_i--){
	if(routes[lhs_i].is_origin){
	  // to right
	  for(int rhs_i = s.rhs + 1; rhs_i < routes.size(); rhs_i++){
	    if(abs(routes[rhs_i].point.imag() - routes[lhs_i].point.imag()) < EPS){
	      double next_cost = s.cost 
		+ compute_distance(routes[s.lhs].point,routes[lhs_i].point)
		+ compute_distance(routes[s.rhs].point,routes[rhs_i].point);
	      if(next_cost < dp[lhs_i][rhs_i]){
		disp(next_cost,lhs_i,rhs_i);
		dp[lhs_i][rhs_i] = next_cost;
		que.push(State(lhs_i,rhs_i,next_cost));
	      }
	      break;
	    }
	    if(routes[rhs_i].is_origin) break;
	  }
	  
	  // to left
	  for(int rhs_i = s.rhs - 1; rhs_i >= 0; rhs_i--){
	    if(abs(routes[rhs_i].point.imag() - routes[lhs_i].point.imag()) < EPS){
	      double next_cost = s.cost 
		+ compute_distance(routes[s.lhs].point,routes[lhs_i].point)
		+ compute_distance(routes[s.rhs].point,routes[rhs_i].point);
	      if(next_cost < dp[lhs_i][rhs_i]){
		disp(next_cost,lhs_i,rhs_i);
		dp[lhs_i][rhs_i] = next_cost;
		que.push(State(lhs_i,rhs_i,next_cost));
	      }
	      break;
	    }
	    if(routes[rhs_i].is_origin) break;
	  }
	  break;
	}
      }
      
    }

    double res = 10000000000000.0;
    for(int pos = 0; pos < routes.size(); pos++){
      res = min(dp[pos][pos],res);
    }
    printf("%.8lf\n",res);
  }
}
